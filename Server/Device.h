/*
  Device.h - Handle the controlled device
  Saul bertuccio 4 feb 2017
  Released into the public domain.
*/

#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "WString.h"
#include "IrKey.h"

// GPIO16 -> D0 ->
// GPIO05 -> D1 -> Pin Ricevitore RF433
// GPIO04 -> D2 -> Pin Trasmettitore RF433  
// GPIO   -> D5 -> RXD Riceve da IR-TXD 
// GPIO   -> D6 -> TXD Trasmette su IR-RXD


class Device {

  public:

    static const int MAX_NAME_LENGTH = 16;

    
    static const int IR_RX_PIN = D5;
    static const int IR_TX_PIN = D6;
 
    Device(const String &dev_name);
    ~Device();

    void setName(const String &new_name);
    
    String getName();
    
    Key * getKeys();

    String * getKeysPropertyNames();
    int getKeysPropertyNum();
    boolean isValidPropertyById(int id, const String &val);

    boolean addKey(String * key_data);
    boolean removeKey(const String &key_name );
    Key * acquireKeyData();
    boolean sendKeyData(const String & key_name);


  private:
    String dev_name;

    Key * first_key = NULL;
    Key * last_key = NULL;

    Key * findPreviousKeyByName(const String &key_name );

    String * getProperties(const String names[], int len);


    static Key * acquireIrKeyData();


    static void sendIrKeyData(Key *key);


};

#endif
