#include "control.h"
#define IR_SEND_LED 12    // GPIO12 = D6

Control::Control(String name, protocol_t protocol) : m_name{name}, m_protocol{protocol} {
    Serial.println("Succesfully created Class Control");
}

uint64_t Control::getCode(function_t function) {
    // EN DESARROLLO devuelve el codigo del control remoto mapeado a su protocolo
    // probablemente un switch case?
    uint64_t code = 0;
    uint32_t size = sizeof(*(m_protocol.functions));
    for (uint32_t i = 0; i < size; i++) {
        if (function == m_protocol.functions[i].function) {
            code = m_protocol.functions[i].code;
            break;
        }  
    }
    return code;
}

// @return True if it is a type we can attempt to send, false if not.
bool Control::send(function_t function, IRsend &irsend) {
    uint64_t code = getCode(function);
    if (code != 0) {
      return irsend.send(m_protocol.name, code, m_protocol.nbits); // lleva parametros nbits y repeat?
    } else {
      return false;
    }
}        


AC_Control::AC_Control(String name, protocol_t protocol) : Control(name, protocol) {
  power = false;
  turbo = false;
  sleep = false;
  led = false;
  swing = false;
  temp = 25;
  fan = 0;
  mode = 0;
  m_state = generateState();
  Serial.println("AC_Control class created");
}

bool AC_Control::send(function_t function, IRsend &irsend) {
    // Sobreescribe Control::send, de esta forma generalizamos todos los controles
    bool ret = true;
    Serial.print("Executing function: ");
    Serial.print(function);

    switch (function) {
        case POWER:
            power = !power;
            if (power) {
                // para prender tiene que generar el estado
                ret = irsend.send(getProtocol(), convertState(), getNBits());
            } else {
                // para apagar manda siempre el mismo estado
                ret = irsend.send(getProtocol(), kCoolixPower, getNBits());
            }
            break;
        case TEMP_UP:
            (temp < maxTemp) ? temp++ : ret = false;
            ret = irsend.send(getProtocol(), convertState(), getNBits());
            break;
        case TEMP_DOWN:
            (temp > minTemp) ? temp-- : ret = false;
            ret = irsend.send(getProtocol(), convertState(), getNBits());
            break;
        case MODE:
            mode = (mode + 1) % sizeof(kCoolixModeMap)/sizeof(uint8_t);
            ret = irsend.send(getProtocol(), convertState(), getNBits());
            break;
        case FAN:
            fan = (fan + 1) % sizeof(kCoolixFanMap)/sizeof(uint8_t); 
            ret = irsend.send(getProtocol(), convertState(), getNBits());
            break;
        case TURBO:
            turbo = !turbo;
            ret = irsend.send(getProtocol(), kCoolixTurbo, getNBits());
            break;
        case SLEEP:
            sleep = !sleep;
            ret = irsend.send(getProtocol(), kCoolixSleep, getNBits());
            break;
        case LED:
            led = !led;
            ret = irsend.send(getProtocol(), kCoolixLight, getNBits());
            break;
        case SWING:
            swing = !swing;
            ret = irsend.send(getProtocol(), kCoolixSwing, getNBits());
            break;
    }
    
    return ret;
}
/*
bool AC_Control::sendState(uint32_t code, IRsend &irsend) {
    return irsend.send(m_protocol, code, nbits);
}
*/
uint32_t AC_Control::convertState() {
    return (m_state.fixed << 19) | (m_state.unk1 << 16) | (m_state.fan << 13) | (m_state.sensor << 8) | (m_state.temp << 4) | (m_state.mode << 2) | (m_state.unk2);
}

state_t AC_Control::generateState() {
    // idealmente es un union o bitfield?
    //uint32_t state = 0b10110 << 26;
    //state |= 0b010 << 
    state_t newState;
    newState.fixed = 0b10110;
    newState.unk1 = 0b010;
    if (mode == 0) newState.fan = kCoolixFanMapCool[fan];
    else newState.fan = kCoolixFanMap[fan];
    newState.sensor = 0b1111;
    newState.temp = kCoolixTempMap[temp-17];
    newState.mode = kCoolixModeMap[mode];
    newState.unk2 = 0b00;

    return newState;
}



uint8_t AC_Control::kCoolixTempMap[14] = {
    0b0000,  // 17C
    0b0001,  // 18C
    0b0011,  // 19C
    0b0010,  // 20C
    0b0110,  // 21C
    0b0111,  // 22C
    0b0101,  // 23C
    0b0100,  // 24C
    0b1100,  // 25C
    0b1101,  // 26C
    0b1001,  // 27C
    0b1000,  // 28C
    0b1010,  // 29C
    0b1011   // 30C
};

uint8_t AC_Control::kCoolixFanMapCool[4] = {
    0b101,  // Auto alt se activa en modo cool
    0b100,  // Min
    0b010,  // Med
    0b001  // Max
    //0b111  // Fixed?
};

uint8_t AC_Control::kCoolixFanMap[4] = {
    0b000,  // Auto
    0b100,  // Min
    0b010,  // Med
    0b001  // Max
    //0b111  // Fixed?
};

uint8_t AC_Control::kCoolixModeMap[4] = {
    0b00,  // Cool
    0b01,  // Dry
    0b10,  // Auto
    0b11  // Heat
    //0b100,  // Fan, 1 bit mas?
};

/*
const uint8_t kCoolingSwingMap[] {
    auto
    low
    mid
    high
}; 
*/
