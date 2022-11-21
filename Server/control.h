#ifndef _CONTROL_H_DEFINED_
#define _CONTROL_H_DEFINED_

#include <Arduino.h> // para usar el Serial.print()
#include <IRsend.h>
#include "protocols.h"

class Control {
    public:
        Control(String name, decode_type_t protocol, key *functions);
        ~Control() {}
        uint32_t getCode(function_t function);
        bool send(function_t function, IRsend &irsend);
        decode_type_t getProtocol();
    private:
        String m_name;
        const decode_type_t m_protocol; 
        key *m_functions;
        uint32_t nbits;
};


class AC_Control : public Control{
    public:
        AC_Control(String name, decode_type_t protocol, key *functions);
        ~AC_Control() {}
        bool readButton(function_t function);
    private:
        const uint8_t maxTemp = 30, minTemp = 17; // Celsius

        //// MAPEOS ////
        const uint32_t kCoolixSleep  = 0b101100101110000000000011;  // 0xB2E003
        const uint32_t kCoolixTurbo  = 0b101101011111010110100010;  // 0xB5F5A2
        const uint32_t kCoolixLight  = 0b101101011111010110100101;  // 0xB5F5A5
        const uint32_t kCoolixClean  = 0b101101011111010110101010;  // 0xB5F5AA
        const uint32_t kCoolixPower  = 0b101100100111101111100000;  // 0xB27BE0

        bool power, turbo, sleep, led;
        uint8_t temp, fan, mode;

        bool send(uint32_t code, IRsend &irsend);
        bool AC_Control::sendState(IRsend &irsend)
        /*bool sendPower();
        bool sendTurbo();
        bool sendSleep();
        bool sendLight();*/
        state_t generateState();
}

#endif
