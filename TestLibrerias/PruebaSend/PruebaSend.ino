/*
 * IRremoteESP8266: IRsendGCDemo
 * demonstrates sending Global Cache-formatted IR codes with IRsend
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * Version 0.2 June, 2017
 *   Added helpful comments
 *   Better includes files.
 * Version 0.1 30 March, 2016
 *   Based on Ken Shirriff's IrsendDemo
 *   Version 0.1 July, 2009
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by IR_LED below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is
 * flashed. Replace the IR LED with a normal LED if you don't have a digital
 * camera when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will
 * interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

// Codes are in Global Cache format less the emitter ID and request ID.
// These codes can be found in GC's Control Tower database.

uint16_t prender_la_tele[145] = {
    3898, 4090,  412, 2084,  440, 2056,  442, 2012,  486, 2008,  488, 1008,  488, 1010,  488, 2010,  488, 1008,  490, 2006,  492, 968,  530, 1968,  530, 968,  530, 970,  526, 970,  502, 998,  524, 974,  526, 1972,  526, 1972,  504, 996,  524, 1974,  498, 1000,  524, 1974,  500, 998,  524, 1974,  524, 8174,  4018, 4016,  484, 2024,  472, 2030,  466, 2062,  408, 2114,  382, 1118,  380, 1144,  354, 2118,  378, 1146,  354, 2142,  356, 1170,  328, 2142,  356, 1196,  276, 1248,  252, 1274,  224, 41396,  132, 2278,  250, 2220,  278, 1274,  224, 1274,  224, 2196,  326, 1198,  302, 2168,  328, 1196,  302, 2170,  302, 1220,  276, 1222,  276, 1222,  276, 1224,  286, 1210,  300, 2198,  300, 2198,  300, 1222,  276, 2222,  276, 1222,  276, 2198,  300, 1198,  300, 2222,  276, 8356,  3720, 4302,  190, 2306,  192, 2306,  190, 2306,  192, 2308,  188, 1334,  146, 1378,  102};
uint64_t data = 0xD5F2A;

#define IR_LED 12  // ESP8266 GPIO pin to use. D6

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

void setup() {
  irsend.begin();
  Serial.begin(115200);
}

void loop() {
  Serial.println("Toggling power");
#if SEND_GLOBALCACHE
  //irsend.sendNikai(data, 24);
  irsend.sendRaw(prender_la_tele, 145, 38);
#else   // SEND_GLOBALCACHE
  Serial.println("Can't send because SEND_GLOBALCACHE has been disabled.");
#endif  // SEND_GLOBALCACHE
  delay(8000);
}
