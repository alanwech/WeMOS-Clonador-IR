#ifndef _CONTROLS_H_DEFINED_
#define _CONTROLS_H_DEFINED_

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
    MUTE
} function_t;

typedef struct {
    uint64_t code;
    function_t function;
} key;


key nikai_functions[] = {
  {0xD5F2A, POWER},
  {0xD0F2F, VOLUME_UP},
  {0xD1F2E, VOLUME_DOWN},
  {0xA6F59, UP},
  {0xA7F58, DOWN},
  {0xA9F56, LEFT},
  {0xA8F57, RIGHT},
  {0xD2F2D, CHANNEL_UP},
  {0xD3F2C, CHANNEL_DOWN},
  {0xD8F27, BACK},
  {0x30FCF, CONFIGURATION},
  {0xF7F08, HOME},
  {0xBFF4, ACCEPT},
  {0xC0F3F, MUTE}
};

typedef struct {
    char *name;
    //protocol_t protocol;
    key *functions;
} control;

#endif
