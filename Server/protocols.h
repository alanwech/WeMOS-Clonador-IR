#ifndef _PROTOCOLS_H_DEFINED_
#define _PROTOCOLS_H_DEFINED_

#include <stdint.h>
#include "IRremoteESP8266.h"

typedef enum decode_type_t decode_type_t;

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

typedef struct {
    uint64_t code;
    function_t function;
} key;

typedef struct protocol_t {
  decode_type_t name;
  key *functions;
  uint32_t functions_length;
  uint32_t nbits;
} protocol_t;

typedef struct state_t {
    uint8_t fixed : 5;
    uint8_t unk1 : 3;
    uint8_t fan : 3;
    uint8_t sensor : 5;
    uint8_t temp : 4;
    uint8_t mode : 2;
    uint8_t unk2 : 2;
} state_t;

extern key nikai_functions[];
extern key rc5_functions[];
extern key epson_functions[];

extern protocol_t Nikai_Protocol;
extern protocol_t RC5_Protocol;
extern protocol_t Epson_Protocol;
extern protocol_t Coolix_Protocol;

#endif
