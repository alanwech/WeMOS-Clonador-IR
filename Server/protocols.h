#ifndef _PROTOCOLS_H_DEFINED_
#define _PROTOCOLS_H_DEFINED_

#include <stdint.h>
#include "IRremoteESP8266.h"

// Enum definido en IRremoteESP8266.h, utilizado para identificar los diferentes protocolos
typedef enum decode_type_t decode_type_t;

// Diferentes funciones de los controles conocidos
typedef enum {
    POWER,
    VOLUME_UP,
    VOLUME_DOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACCEPT,
    CHANNEL_UP,
    CHANNEL_DOWN,
    BACK,
    CONFIGURATION,
    HOME,
    MUTE,
    MENU,
    SOURCE,
    HELP,
    PAGE_UP,
    PAGE_DOWN,
    ZOOM_IN,
    ZOOM_OUT,
    FREEZE,
    AUTO,       // proyector
    VOLUME,      // proyector
    TEMP_UP,
    TEMP_DOWN,
    MODE,
    FAN,
    TURBO,
    SLEEP,
    LED,
    SWING
} function_t;

// Estructura que almacena la trama IR correspondiente a una funcion
typedef struct {
    uint64_t code;
    function_t function;
} key;

// Estructura que almacena la informacion de un protocolo
typedef struct protocol_t {
  decode_type_t name;
  key *functions;
  uint32_t functions_length;
  uint32_t nbits;
} protocol_t;


extern key nikai_functions[];
extern key rc5_functions[];
extern key sony_functions[];
extern key epson_functions[];

extern protocol_t Nikai_Protocol;
extern protocol_t RC5_Protocol;
extern protocol_t Epson_Protocol;
extern protocol_t Sony_Protocol;
extern protocol_t Coolix_Protocol;

#endif
