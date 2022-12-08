#include "control.h"

// Constructor
Control::Control(String name, protocol_t protocol) : m_name{name}, m_protocol{protocol} {
}

/// @brief Mapea una determinada funcion al codigo IR correspondiente
/// @param function Funcion que se quiere transmitir
/// @return Codigo 64 bits que representa la trama IR
uint64_t Control::getCode(function_t function) {
    uint64_t code = 0;
    for (uint32_t i = 0; i < m_protocol.functions_length; i++) {
        if (function == m_protocol.functions[i].function) {
            code = m_protocol.functions[i].code;
            break;
        }  
    }
    Serial.println(code);
    return code;
}

/// @brief Envía una trama IR
/// @param function Funcion que se desea realizar con el control
/// @param irsend Referencia al objeto IRsend que maneja la transmision IR
/// @return True si se envió sin errores, False en caso contrario
bool Control::send(function_t function, IRsend &irsend) {
    uint64_t code = getCode(function);
    if (code != 0) {
      return irsend.send(m_protocol.name, code, m_protocol.nbits);
    } else {
      return false;
    }
}        

/// @brief Constructor de clase AC_Control
/// @param name Nombre del control
/// @param protocol Protocolo que utiliza
AC_Control::AC_Control(String name, protocol_t protocol) : Control(name, protocol) {
    initializeState();
}

/// @brief Envía el estado del A/C codificado en una trama IR
/// @param function Funcion que se desea realizar con el control
/// @param irsend Referencia al objeto IRsend que maneja la transmision IR
/// @return True si se envió sin errores, False en caso contrario
bool AC_Control::send(function_t function, IRsend &irsend) {
    // Sobreescribe Control::send, de esta forma generalizamos todos los controles
    bool ret = true;

    uint32_t code;

    Serial.println("AC_Control.send");

    switch (function) {
        case POWER:
            power = !power;
            // para prender tiene que generar el estado, para apagar manda siempre el mismo estado
            code = (power) ? convertState() : kCoolixPower; 
            break;
        case TEMP_UP:
            (temp < maxTemp) ? temp++ : ret = false;
            code = convertState();
            break;
        case TEMP_DOWN:
            (temp > minTemp) ? temp-- : ret = false;
            code = convertState();
            break;
        case MODE:
            mode = (mode + 1) % sizeof(kCoolixModeMap)/sizeof(uint8_t);
            code = convertState();
            break;
        case FAN:
            fan = (fan + 1) % sizeof(kCoolixFanMap)/sizeof(uint8_t); 
            code = convertState();
            break;
        case TURBO:
            turbo = !turbo;
            code = kCoolixTurbo;
            break;
        case SLEEP:
            sleep = !sleep;
            code = kCoolixSleep;
            break;
        case LED:
            led = !led;
            code = kCoolixLight;
            break;
        case SWING:
            swing = !swing;
            code = kCoolixSwing;
            break;
    }

    Serial.print("Codigo: ");
    Serial.println(code);
    ret = irsend.send(getProtocol(), code, getNBits());
    
    return ret;
}

/// @brief Inicializa el estado del A/C
void AC_Control::initializeState() {
  Serial.println("Iniciando state");
  power = false;    // Apagado
  turbo = false;    // Turbo = false
  sleep = false;    // Sleep = false
  led = false;      // Led = apagado
  swing = false;    // Swing = apagado
  temp = 25;        // Temperatura = 25°C
  fan = 0;          // Ventilador = automatico
  mode = 0;         // Modo = automatico
  updateState();
}

/// @brief Codifica el estado del A/C en un codigo de 32 bits para transmitirlo
/// @return Codigo de 32 bits a transmitir
uint32_t AC_Control::convertState() {
    updateState();
    return (m_state.fixed << 19) | (m_state.unk1 << 16) | (m_state.fan << 13) | (m_state.sensor << 8) | (m_state.temp << 4) | (m_state.mode << 2) | (m_state.unk2);
}

/// @brief Actualiza el estado del A/C en funcion de las variables
void AC_Control::updateState() {
    m_state.fixed = 0b10110;
    m_state.unk1 = 0b010;
    if (mode == 0) m_state.fan = kCoolixFanMapCool[fan];
    else m_state.fan = kCoolixFanMap[fan];
    m_state.sensor = 0b1111;
    m_state.temp = kCoolixTempMap[temp-17];
    m_state.mode = kCoolixModeMap[mode];
    m_state.unk2 = 0b00;
}

/// @brief Convierte el estado del A/C a un JSON para enviar a la web
/// @return JSON que contiene el estado del A/C
DynamicJsonDocument AC_Control::toJSON(){
    DynamicJsonDocument doc(512);

    doc["power"] = power;
    doc["turbo"] = turbo;
    doc["sleep"] = sleep;
    doc["led"] = led;
    doc["swing"] = swing;
    doc["temp"] = temp;
    doc["fan"] = fan;
    doc["mode"] = mode;

    return doc;
}


/* Definicion de arrays constantes */

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
};

uint8_t AC_Control::kCoolixFanMap[4] = {
    0b000,  // Auto
    0b100,  // Min
    0b010,  // Med
    0b001   // Max
};

uint8_t AC_Control::kCoolixModeMap[4] = {
    0b00,  // Cool
    0b01,  // Dry
    0b10,  // Auto
    0b11   // Heat
};

/* ------------------- */
