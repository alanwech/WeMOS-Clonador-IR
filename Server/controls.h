#ifndef _CONTROLS_H_DEFINED_
#define _CONTROLS_H_DEFINED_

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
    VOLUME      // proyector
} function_t;

typedef struct {
    uint64_t code;
    function_t function;
} key;

typedef struct {
    char *name;
    decode_type_t protocol;
    key *functions;
} control_t;

extern key nikai_functions[];
extern key rc5_functions[];
extern key epson_functions[];

extern uint64_t getCode(control_t *control, function_t *function);

#endif
