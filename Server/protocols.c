#include "protocols.h"

protocol_t Nikai_Protocol = {NIKAI, nikai_functions, 24};

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

protocol_t RC5_Protocol = {RC5, rc5_functions, 16};

key rc5_functions[] = {
  {0x80C, POWER},
  {0x810, VOLUME_UP},
  {0x811, VOLUME_DOWN},
  {0x820, CHANNEL_UP},
  {0x821, CHANNEL_DOWN}
};

protocol_t Epson_Protocol = {EPSON, epson_functions, 32};

key epson_functions[] = {
  {0xC1AA09F6, POWER},
  {0xC1AA0DF2, UP},
  {0xC1AA4DB2, DOWN},
  {0xC1AACD32, LEFT},
  {0xC1AA8D72, RIGHT},
  {0xC1AAA15E, ACCEPT},
  {0xC1AA59A6, MENU},
  {0xC1AA21DE, BACK},
  {0xC1AA31CE, SOURCE},
  {0xC1AAA956, HELP},
  {0xC1AA7986, AUTO},
  {0xC1AABE41, VOLUME},
  {0xC1AA619E, PAGE_UP},
  {0xC1AAE11E, PAGE_DOWN},
  {0xC1AA11EE, ZOOM_IN},
  {0xC1AA916E, ZOOM_OUT},
  {0xC1AA49B6, FREEZE},
  {0xC1AAC936, MUTE}
};

protocol_t Coolix_Protocol = {COOLIX, 0, 24};
