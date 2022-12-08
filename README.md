- [WeMOS-Clonador-IR](#wemos-clonador-ir)
  - [Librerías utilizadas](#librerías-utilizadas)
  - [Instalación y requerimientos](#instalación-y-requerimientos)
  - [Cómo usar](#cómo-usar)
    - [Server.ino](#serverino)
    - [Pagina.h](#paginah)
    - [Control.h](#controlh)
    - [Protocols.h](#protocolsh)
  - [Formas de contribuir](#formas-de-contribuir)

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


## Cómo usar
### Server.ino
El archivo principal donde se levanta la página y se encuentra la lógica. Aquí podremos seleccionar si se utiliza el dispositivo como access point o con una red wifi independiente, asignar la SSID/Password correspondiente, agregar mensajes de debug, seleccionar los GPIO de datos del receptor/emisor IR y manejar las peticiones HTTP desde y hacia la página.
### Pagina.h
Aquí se almacena el diseño de la página.
### Control.h
Contiene las clases derivadas de Control y los métodos correspondientes, los cuales pueden variar dependiendo del tipo de control, en el caso de los aires acondicionados la clase es más compleja ya que almacena y envía un estado en la mayoría de los mensajes y la solución para el protocolo elegido es ad-hoc.
En cambio en el caso de los controles de TV/Proyector estos envían un código correspondiente a una acción, sin necesidad de saber el estado del mismo.
### Protocols.h
Contiene los protocolos definidos junto con estructuras de datos para guardar los códigos conocidos.

## Formas de contribuir
Por diversos motivos no se llegó a implementar algunas características de gran valor para el proyecto.
- Investigar y agregar más integraciones a nuevos protocolos de A/C, por ejemplo Kelon168
- Agregar más controles remotos de TV/Proyector
- Posibilidad de agregar controles de TV o proyector (que envíen mensajes fijos en lugar de estados como en los de A/C) en runtime
