/*
  Device.cpp - Handle the controlled device implementation
  Saul bertuccio 4 feb 2017
  Released into the public domain.
*/

#include "Device.h"


Device::Device(const String &dev_name)
  : dev_name(dev_name)
{}

Device::~Device() {

  while (first_key) {
    Key * k = first_key->getNext();
    delete first_key;
    first_key = k;
  }
}

void Device::setName(const String &new_name) { dev_name = new_name; }

String Device::getName() {  return dev_name; }

boolean Device::isValidPropertyById(int id, const String &val) {
  
  return IrKey::validations[id](val);
    
  return false;
}

int Device::getKeysPropertyNum() {

  return IrKey::props_num;

}

String * Device::getKeysPropertyNames() {

  int len = 0;
  String * prop = NULL;
  
  return getProperties(IrKey::props_names, IrKey::props_num);
    

}

Key * Device::getKeys() { return first_key; };


boolean Device::addKey(String * key_data) {

  Key *key;

  // Check name
  if (key_data[0].length() > Key::MAX_KEY_NAME_LEN)
    return false;

  key = new IrKey( key_data[0], key_data[1] );
    
  if (!key)
    return false;

  if ( first_key == NULL ) {
    first_key = key;
    last_key = key;
  } else {
    last_key->setNext(key);
    last_key = key;
  }
  return true;
}

boolean Device::sendKeyData(const String & key_name) {

  Key * k = findPreviousKeyByName(key_name);

  if ( k == NULL) {
    if (first_key != NULL && first_key->getName() == key_name) {
      k = first_key;
    } else {
      return false;
    }
  } else {
    k = k->getNext();
  }

  
  Device::sendIrKeyData(k);

  return true;  
}

Key * Device::acquireKeyData() {

  // IRDA
  Key * k;
  
  k = Device::acquireIrKeyData();

  return k;
}


boolean Device::removeKey(const String &key_name ) {
  
  Key * prev_key = this->findPreviousKeyByName( key_name );

  if ( prev_key == NULL) {
    
    if ( first_key == NULL || first_key->getName() != key_name ) {
      return false;
    }
      
    prev_key = first_key;
    first_key = prev_key->getNext();
    delete prev_key;

    if ( first_key == NULL ) {
      last_key = NULL;
    }

    return true;
  }

  Key * next_key = prev_key->getNext();

  prev_key->setNext(next_key->getNext());

  if (next_key == last_key) {
    
    last_key = prev_key;

  }

  delete next_key;
  return true;
}

Key * Device::findPreviousKeyByName(const String &key_name) {

  if (first_key == NULL)
    return NULL;

  Key * key = first_key;

  while (Key * next = key->getNext()) {
    
    if ( next->getName() == key_name ) {
      return key;
    }
 
    key = next;
  }

  return NULL;
  
}

String * Device::getProperties(const String names[], int len) {

    String * props = new String[len];
    
    for (int i = 0; i < len; i++) {
    props[i] = names[i];
  }

  return props;
}


void Device::sendIrKeyData(Key *key) {

  static String hex_decode = "0123456789ABCDEF"; 
  IrKey *k = static_cast<IrKey *>(key);
  String code = k->getCode().substring(2);
  code.toUpperCase();

  if (code.length() % 2 != 0) {
    Serial.println("Errore: Codice da inviare valido");
    return;
  }

  SoftwareSerial sw(IR_RX_PIN, IR_TX_PIN, false);
  int i=0;
  sw.begin(9600);
  // Protocollo
  sw.write(0xA1);
  sw.write(0xF1);
  while (i < code.length()) {
    char n = hex_decode.indexOf(code[i++]) << 4;
    n +=  hex_decode.indexOf(code[i++]);
    sw.write(n);
  }
}


Key * Device::acquireIrKeyData() {

  static char const hex_encode[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
  char code[11] = {'0', 'x', '\0'};
  SoftwareSerial sw(IR_RX_PIN, IR_TX_PIN, false);
  sw.begin(9600, SWSERIAL_8N1, IR_RX_PIN, IR_TX_PIN, false);
  boolean is_code_ok = false;

  Serial.println("Checking RX pin");
  Serial.println(sw.testPin(IR_RX_PIN));
  Serial.println("Checking TX pin");
  Serial.println(sw.testPin(IR_TX_PIN));
  
  if (!sw) {
    Serial.println("UART not working");
  }
  int attempt = 3;
  for (int i=0; i < attempt; i++) {
    delay(500);
    int p = 2;
    while (sw.available() > 0 && p < 15) {
      char c = sw.read();
      Serial.print(c);
      code[p++] = hex_encode[ ( c & 0xF0 ) >> 4  ];
      code[p++] = hex_encode[ (c & 0x0F ) ];
      delay(40);
    }
    sw.flush();
    code[p] = '\0';
    if (p>4) {
      is_code_ok=true;
      break;
    }
  }

  IrKey * ir = NULL;
  if (is_code_ok) {
    ir = new IrKey("DUMMY", String(code));
  }
  return ir;
}
