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

/*
class AC_Control : public Control{
    public:
        AC_Control(String name, decode_type_t protocol, key *functions);
        ~AC_Control() {}
        bool sendEstado();
        bool readButton(function_t function);
    private:
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

        bool sendPower();
        bool sendTurbo();
        bool sendSleep();
        bool sendLight();
        state_t generateState();
}
*/

#endif
