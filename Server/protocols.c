#include "protocols.h"

/*  Este archivo define los protocolos conocidos.
 *  Para cada protocolo se define :
 *  - decode_type_t name: identificador del protocolo (decode_type_t definido en la libreria IRremote)
 *  - key *functions: array de funciones que contiene la trama IR correspondiente a cada funcion
 *  - functions_length: longitud del array de funciones
 *  - nbits: longitud en bits de la trama a transmitir
 *  
 *  Junto con cada protocol_t se define el array de funciones correspondiente.
 */

#define NIKAI_LENGTH  15
#define RC5_LENGTH    15
#define SONY_LENGTH   15
#define EPSON_LENGTH  18

/* Protocolo Nikai */
protocol_t Nikai_Protocol = {NIKAI, nikai_functions, NIKAI_LENGTH, 24};

key nikai_functions[NIKAI_LENGTH] = {
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
  {0xC0F3F, MUTE},
  {0x5CFA3, SOURCE}
};
/* --------------- */


/* Protocolo RC5 */
protocol_t RC5_Protocol = {RC5, rc5_functions, RC5_LENGTH, 12};

key rc5_functions[RC5_LENGTH] = {
  {0x80C, POWER},
  {0x810, VOLUME_UP},
  {0x811, VOLUME_DOWN},
  {0x820, CHANNEL_UP},
  {0x821, CHANNEL_DOWN},
  {0x82F, UP},
  {0x830, DOWN},
  {0x831, LEFT},
  {0x833, RIGHT},
  {0x81F, BACK},
  {0x82E, CONFIGURATION},
  {0x82E, HOME},
  {0x81B, ACCEPT},
  {0x80D, MUTE},
  {0x838, SOURCE}
};
/* --------------- */

/* Protocolo Sony */
protocol_t Sony_Protocol = {SONY, sony_functions, SONY_LENGTH, 12};

key sony_functions[SONY_LENGTH] = {
  {0xA90, POWER},
  {0x490, VOLUME_UP},
  {0xC90, VOLUME_DOWN},
  {0x90, CHANNEL_UP},
  {0x890, CHANNEL_DOWN},
  {0x2F0, UP},
  {0xAF0, DOWN},
  {0x2D0, LEFT},
  {0xCD0, RIGHT},
  {0xDD0, BACK},
  {0x70, MENU},
  {0x70, HOME},
  {0xA70, ACCEPT},
  {0x290, MUTE},
  {0xA50, SOURCE}
};
/* --------------- */

/* Protocolo EPSON */
protocol_t Epson_Protocol = {EPSON, epson_functions, EPSON_LENGTH, 32};

key epson_functions[EPSON_LENGTH] = {
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
/* --------------- */


// Los protocolos de A/C no tienen una lista de funciones, por lo que no se definen los campos functions y functions_length 

/* Protocolo Coolix */
protocol_t Coolix_Protocol = {COOLIX, 0, 0, 24};
/* --------------- */
