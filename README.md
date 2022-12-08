# WeMOS-Clonador-IR
Sistema de escaneo, administración y clonado de controles remotos infrarrojos.

## Librerías utilizadas
- [IRremoteESP8266 - 2.8.4](https://github.com/crankyoldgit/IRremoteESP8266)
- [Arduino core for ESP8266 WiFi - 3.0.2](https://github.com/esp8266/Arduino)
- [ArduinoJson - 6.19.4](https://github.com/bblanchon/ArduinoJson)


## Instalación y requerimientos
Para levantar el servidor y poder hacer uso de las funcionalidades desarrolladas será necesario disponer de las librerías previamente mencionadas (incluídas en `/Server/lib/.`), se recomienda fuertemente mantener las versiones utilizadas para evitar problemas de compatibilidad.
En cuanto al hardware es necesario cualquier variante de ESP8266, en nuestro caso utilizamos una **WeMOS D1R2** pero el código es compatible con cualquier embebido que contenga dicho microcontrolador, deberán configurarse las entradas/salidas a utilizar en el #define de código.
Tanto el emisor como el receptor IR envían el mensaje modulado @ 38KHz.

- ESP8266 / WeMOS
- KY-022 (Receptor IR)
- KY-005 (Emisor IR)


## Formas de contribuir
Por diversos motivos no se llegó a implementar algunas características de grán valor para el proyecto.
- Investigar y agregar más integraciones a nuevos protocolos de A/C, por ejemplo Kelon168
- Agregar más controles remotos de TV/Proyector
- Posibilidad de agregar controles de TV o proyector (que envíen mensajes fijos en lugar de estados como en los de A/C) en runtime
