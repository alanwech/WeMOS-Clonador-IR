#include "controls.h"

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

key rc5_functions[] = {
  {0x80C, POWER},
  {0x810, VOLUME_UP},
  {0x811, VOLUME_DOWN},
  {0x820, CHANNEL_UP},
  {0x821, CHANNEL_DOWN}
};

key epson_functions[] = {
  {0xC1AA09F6, POWER},
  {0xC1AA0DF2, UP},
  {0xC1AA4DB2, DOWN},
  {0xC1AACD32, LEFT},
  {0xC1AA8D72, RIGHT},
  {0xC1AAA15E, ACCEPT},
  {0xC1AA59A6, MENU},
  {0xC1AA21DE, BACK}
};