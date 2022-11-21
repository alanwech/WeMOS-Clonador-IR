#include "control.h"
#define IR_SEND_LED 12    // GPIO12 = D6

Control::Control(String name, decode_type_t protocol, key *functions)
        : m_name{name}, m_protocol{protocol}, m_functions{functions}  {
    Serial.println("Succesfully created Class Control");
}

uint32_t Control::getCode(function_t function) {
    // EN DESARROLLO devuelve el codigo del control remoto mapeado a su protocolo
    // probablemente un switch case?
    uint64_t code = 0;
    uint32_t size = sizeof(*(m_functions));
    for (uint32_t i = 0; i < size; i++) {
        if (function == m_functions[i].function) {
            code = m_functions[i].code;
            break;
        }  
    }
    return code;
}

// @return True if it is a type we can attempt to send, false if not.
bool Control::send(function_t function, IRsend &irsend) {
    uint64_t code = getCode(function);
    if (code != 0) {
      return irsend.send(m_protocol, getCode(function), nbits); // lleva parametros nbits y repeat?
    } else {
      return false;
    }
}        

decode_type_t Control::getProtocol() {
    return m_protocol;
}



/*
AC_Control::AC_Control(String name, decode_type_t protocol, key *functions) : Control(name, protocol, functions) {
    Serial.println("AC_Control class created");
}

bool AC_Control::sendEstado() {
    state_t estado = generateState();
    Serial.print(estado); // VER SI NO ROMPE
    return irsend.send(m_protocol, estado); // lleva parametros nbits y repeat?
}

bool AC_Control::readButton(function_t function) {
    bool ret = true;
    Serial.print("Executing function: ");
    Serial.print(function);
    switch (function) {
        case "POWER":
            power = !power;
            sendPower();
            break;
        case "TEMP_UP":
            (temp < maxTemp) ? temp++ : ret = false;
            ret = sendEstado();
            break;
        case "TEMP_DOWN":
            (temp > minTemp) ? temp-- : ret = false;
            ret = sendEstado();
            break;
        case "MODE":
            (mode == (sizeof(kCoolixModeMap)/sizeof(uint8_t) - 1)) ? mode = 0 : mode++;
            ret = sendEstado();
            break;
        case "FAN":
            (mode == (sizeof(kCoolixFanMap)/sizeof(uint8_t) - 1)) ? fan = 0 : fan++;
            ret = sendEstado();
            break;
        case "TURBO":
            turbo = !turbo;
            sendTurbo();
            break;
        case "SLEEP":
            sleep = !sleep;
            sendSleep();
            break;
        case "LED":
            led = !led;
            sendLight();
            break;
        case "SWING":
            // pendiente implementacion
            break;
    }
    
    return ret;
}

private:
//// VARIABLES ////
const uint8_t maxTemp = 30, minTemp = 17; // Celsius
bool power, turbo, sleep, led;
uint8_t temp, fan, mode;

typedef {
    uint8_t fixed : 5;
    uint8_t unk1 : 3;
    uint8_t fan : 3;
    uint8_t sensor : 5;
    uint8_t temp : 4;
    uint8_t mode : 2;
    uint8_t unk2 : 2;
} struct state_t;

//// MAPEOS ////
const uint32_t kCoolixSleep  = 0b101100101110000000000011;  // 0xB2E003
const uint32_t kCoolixTurbo  = 0b101101011111010110100010;  // 0xB5F5A2
const uint32_t kCoolixLight    = 0b101101011111010110100101;  // 0xB5F5A5
const uint32_t kCoolixClean  = 0b101101011111010110101010;  // 0xB5F5AA
const uint32_t kCoolixPower    = 0b101100100111101111100000;  // 0xB27BE0

const uint8_t kCoolixTempMap[] = {
    0b0000,  // 17C
    0b0001,  // 18c
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

const uint8_t kCoolixFanMap[] = {
    0b000,  // Auto se activa en modo auto
    //0b101,  // Auto alt se activa en modo cool
    0b100,  // Min
    0b010,  // Med
    0b001  // Max
    //0b111  // Fixed?
};

const uint8_t kCoolixModeMap[] = {
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
* /

//// FUNCIONES ////
bool sendPower() {
    return irsend.send(m_protocol, kCoolixPower); // lleva parametros nbits y repeat?
}

bool sendTurbo() {
    return irsend.send(m_protocol, kCoolixTurbo); // lleva parametros nbits y repeat?
}

bool sendSleep() {
    return irsend.send(m_protocol, kCoolixSleep); // lleva parametros nbits y repeat?
}
bool sendLight() {
    return irsend.send(m_protocol, kCoolixLight); // lleva parametros nbits y repeat?
}

state_t generateState() {
    // idealmente es un union o bitfield?
    //uint32_t state = 0b10110 << 26;
    //state |= 0b010 << 
    state_t newState;
    newState.fixed = 0b10110;
    newState.unk1 = 0b010;
    newState.fan = kCoolixFanMap[fan];
    newState.sensor = 0b1111;
    newState.temp = kCoolixTempMap[temp];
    newState.mode = kCoolixModeMap[mode];
    newState.unk2 = 0b00;

    return newState;
}
*/
