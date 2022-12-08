#ifndef _CONTROL_H_DEFINED_
#define _CONTROL_H_DEFINED_

#include <Arduino.h> // para usar el Serial.print()
#include <ArduinoJson.h> // para parsear a JSON
#include <IRsend.h>
#include "protocols.h"

// Estructura que almacena el estado de un A/C Coolix
typedef struct state_t {
    uint8_t fixed : 5;
    uint8_t unk1 : 3;
    uint8_t fan : 3;
    uint8_t sensor : 5;
    uint8_t temp : 4;
    uint8_t mode : 2;
    uint8_t unk2 : 2;
} state_t;

/*
 * Clase Control
 * Simula cualquier control infrarrojo simple como los de un TV o un proyector.
 */
class Control {
    public:
        Control(String name, protocol_t protocol);
        ~Control() {}
        virtual bool send(function_t function, IRsend &irsend);
        
        String getName() { return m_name; }
        decode_type_t getProtocol() { return m_protocol.name; }
        uint32_t getNBits() { return m_protocol.nbits; }
    private:
        String m_name;
        const protocol_t m_protocol; 

        uint64_t getCode(function_t function);
};

/*
 * Clase AC_Control (subclase de Control)
 * Su funcion es controlar aires acondicionados.
 * Por el momento solo se cuenta con el protocolo Coolix
 */
class AC_Control : public Control{
    public:
        AC_Control(String name, protocol_t protocol);
        ~AC_Control() {}
        bool send(function_t function, IRsend &irsend);
        DynamicJsonDocument toJSON();
    private:
        static const uint8_t maxTemp = 30, minTemp = 17; // Celsius

        //// MAPEOS ////
        static const uint32_t kCoolixSleep  = 0xB2E003;   // 0b101100101110000000000011; 
        static const uint32_t kCoolixTurbo  = 0xB5F5A2;   // 0b101101011111010110100010; 
        static const uint32_t kCoolixLight  = 0xB5F5A5;   // 0b101101011111010110100101; 
        static const uint32_t kCoolixClean  = 0xB5F5AA;   // 0b101101011111010110101010; 
        static const uint32_t kCoolixPower  = 0xB27BE0;   // 0b101100100111101111100000; 
        static const uint32_t kCoolixSwing  = 0xB26BE0;   // 0b101100100110101111100000;

        static uint8_t kCoolixTempMap[14];
        static uint8_t kCoolixFanMap[4];
        static uint8_t kCoolixFanMapCool[4];
        static uint8_t kCoolixModeMap[4];

        bool power, turbo, sleep, led, swing;
        uint8_t temp, fan, mode;
        state_t m_state;

        void initializeState();
        void updateState();
        uint32_t convertState();
};

#endif
