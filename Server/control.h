#ifndef _CONTROL_H_DEFINED_
#define _CONTROL_H_DEFINED_

#include <Arduino.h> // para usar el Serial.print()
#include <ArduinoJson.h> // para parsear a JSON
#include <IRsend.h>
#include "protocols.h"

class Control {
    public:
        Control(String name, protocol_t protocol);
        ~Control() {}
        bool send(function_t function, IRsend &irsend);
        decode_type_t getProtocol() { return m_protocol.name; }
        uint32_t getNBits() { return m_protocol.nbits; }
    private:
        String m_name;
        const protocol_t m_protocol; 

        uint64_t getCode(function_t function);
};


class AC_Control : public Control{
    public:
        AC_Control(String name, protocol_t protocol);
        ~AC_Control() {}
        bool send(function_t function, IRsend &irsend);
        DynamicJsonDocument toJSON();
    private:
        static const uint8_t maxTemp = 30, minTemp = 17; // Celsius

        //// MAPEOS ////
        static const uint32_t kCoolixSleep  = 0b101100101110000000000011;  // 0xB2E003
        static const uint32_t kCoolixTurbo  = 0b101101011111010110100010;  // 0xB5F5A2
        static const uint32_t kCoolixLight  = 0b101101011111010110100101;  // 0xB5F5A5
        static const uint32_t kCoolixClean  = 0b101101011111010110101010;  // 0xB5F5AA
        static const uint32_t kCoolixPower  = 0b101100100111101111100000;  // 0xB27BE0
        static const uint32_t kCoolixSwing  = 0xB26BE0;

        static uint8_t kCoolixTempMap[14];
        static uint8_t kCoolixFanMap[4];
        static uint8_t kCoolixFanMapCool[4];
        static uint8_t kCoolixModeMap[4];

        bool power, turbo, sleep, led, swing;
        uint8_t temp, fan, mode;
        state_t m_state;

        //bool sendState(uint32_t code, IRsend &irsend);
        uint32_t convertState();
        state_t generateState();
};

#endif
