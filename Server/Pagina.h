const char webpage[] = 
  R"=====(
  <!DOCTYPE html>
  <html>
      <style type="text/css">
          .button {
              background-color: #4CAF50;
              border: 1px solid;
              border-color: black;
              border-radius: 5px;
              flex: auto;
              color: white;
              padding: 15px 32px;
              text-align: center;
              display: inline-block;
              font-size: 16px;
          }
          .col {
              float: left;
              width: 23.33%;
              padding-left: 5%;
              padding-right: 5%;
              height: 30px;
              display: flex;
              align-items: center;
          }
          .row:after {
              content: "";
              display: flex;
              clear: both;
          }
          .centrar {
              width: 400px;
              padding: 10px;
              margin:auto;
          }

          .fila {
            display: flex;
          }

          .columna {
            flex: 50%;
          }
  
      </style>
      <body onload="init()">
          <div style="text-align: center;">
              <h1>Clonador de Controles Infrarrojos</h1>
          </div>
          <div class="container">
              <div class="row">
                  <div class="col">
                      <button class="button" onclick="display('tv_lucho')">Television</button>
                  </div>
                  <div class="col">
                      <button class="button" onclick="display('aire')">Aire Acondicionado</button><BR>
                  </div>
                  <div class="col">
                      <button class="button" onclick="display('proyector')">Proyector</button><BR>
                  </div>
              </div>
          </div><br><hr><br>
          <div id="tv_lucho"  style="display:none;">
              <div class="row centrar">
                  <div class="col  centrar" >
                      <button class="button" style="background-color: #f32c2c" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="send_command(buttons['CHANNEL_UP'])">CANAL +</button>
                      <button class="button" onclick="send_command(buttons['CHANNEL_DOWN'])">CANAL -</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="send_command(buttons['VOLUME_UP'])">VOL +</button>
                      <button class="button" onclick="send_command(buttons['VOLUME_DOWN'])">VOL -</button>
                  </div>
              </div>
              <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['UP'])">^</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['LEFT'])"><</button>
                    <button class="button" onclick="send_command(buttons['ACCEPT'])">OK</button>
                    <button class="button" onclick="send_command(buttons['RIGHT'])">></button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['DOWN'])">v</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['HOME'])">HOME</button>
                    <button class="button" onclick="send_command(buttons['MUTE'])">MUTE</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['BACK'])">BACK</button>
                    <button class="button" onclick="send_command(buttons['CONFIGURATION'])">CONF</button>
                </div>
            </div>
          </div>
          <div id="aire"  style="display:none;" class="container" >
            <div class="fila">
                <div class="columna">
                    <div class="row centrar">
                        <div class="col  centrar" >
                            <button class="button" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <button class="button" onclick="aire_modo()">MODO</button>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <button class="button" onclick="aire_temp('up')">TEMP +</button>
                            <button class="button" onclick="aire_temp('down')">TEMP -</button>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <button class="button" onclick="aire_vel()">VELOCIDAD</button>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <button class="button" onclick="send_command(buttons['SLEEP'])">SWING</button>
                        </div>
                    </div>
                </div>
                <div class="columna">
                    <div class="row centrar">
                        <div class="col centrar">
                            <h2>Estado: <span id="estado"></span></h2>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <h2>Modo: <span id="modo"></span></h2>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <h2>Temperatura: <span id="temp"></span> C</h2>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <h2>Velocidad: <span id="vel"></span></h2>
                        </div>
                    </div>
                    <div class="row centrar">
                        <div class="col centrar">
                            <h2>Swing: <span id="swing"></span></h2>
                        </div>
                    </div>
                </div>
            </div>
            <div class = "row centrar">
                <div class="col centrar">
                    <button class="button" style="background-color: #f32c2c" onclick="send_state()">ENVIAR ESTADO</button>
                </div>
            </div>
          </div>
          <div id="proyector"  style="display:none;">
            <div class="row centrar">
                <div class="col  centrar" >
                    <button class="button" style="background-color: #f32c2c" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                    <button class="button" onclick="send_command(buttons['SOURCE'])">SOURCE</button>
                    <button class="button" onclick="send_command(buttons['HELP'])">HELP</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['MENU'])">MENU</button>
                    <button class="button" onclick="send_command(buttons['UP'])">^</button>
                    <button class="button" onclick="send_command(buttons['BACK'])">BACK</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['LEFT'])"><</button>
                    <button class="button" onclick="send_command(buttons['ACCEPT'])">OK</button>
                    <button class="button" onclick="send_command(buttons['RIGHT'])">></button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['AUTO'])">AUTO</button>
                    <button class="button" onclick="send_command(buttons['DOWN'])">v</button>
                    <button class="button" onclick="send_command(buttons['VOLUME'])">VOLUME</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['PAGE_UP'])">PAGE+</button>
                    <button class="button" onclick="send_command(buttons['ZOOM_IN'])">ZOOM+</button>
                    <button class="button" onclick="send_command(buttons['FREEZE'])">FREEZE</button>
                </div>
            </div>
            <div class="row centrar">
                <div class="col centrar">
                    <button class="button" onclick="send_command(buttons['PAGE_DOWN'])">PAGE-</button>
                    <button class="button" onclick="send_command(buttons['ZOOM_OUT'])">ZOOM-</button>
                    <button class="button" onclick="send_command(buttons['MUTE'])">MUTE</button>
                </div>
            </div>
        </div>
          <script>
              const buttons = {
                'POWER': 0,
                'VOLUME_UP':1,
                'VOLUME_DOWN':2,
                'UP':3,
                'DOWN':4,
                'LEFT':5,
                'RIGHT':6,
                'ACCEPT':7,
                'CHANNEL_UP':8,
                'CHANNEL_DOWN':9,
                'BACK':10,
                'CONFIGURATION':11,
                'HOME':12,
                'MUTE':13,
                'MENU':14,
                'SOURCE':15,
                'HELP':16,
                'PAGE_UP':17,
                'PAGE_DOWN':18,
                'ZOOM_IN':19,
                'ZOOM_OUT':20,
                'FREEZE':21,
                'AUTO':22,
                'VOLUME':23,
                'TEMP_UP':24,
                'TEMP_DOWN':25,
                'MODE':26,
                'FAN':27,
                'TURBO':28,
                'SLEEP':29,
                'LED':30,
                'SWING':31
              }

              const modos = {
                0 : 'FRIO',
                1 : 'CALOR',
                2 : 'HUMEDAD',
                3 : 'VENTILADOR'
              }

              const velocidades = {
                0 : 'AUTOMATICA',
                1 : 'BAJA',
                2 : 'MEDIA',
                3 : 'ALTA'
              }

              const devices = ['tv_lucho','aire','proyector']

              var modo = 0
              var temperatura = 20
              var velocidad = 0
              var estado = false
              var swing = false
              var device

              function init(){
                document.getElementById("modo").innerHTML = modos[modo]
                document.getElementById("estado").innerHTML = 'APAGADO'
                document.getElementById("temp").innerHTML = temperatura
                document.getElementById("vel").innerHTML = velocidades[velocidad]
                document.getElementById("swing").innerHTML = 'NO'
              }

              function display(id) {
                devices.forEach(element => {
                    if (element == id){
                        document.getElementById(element).style.display = "block"
                        device = id;

                    } else {
                        document.getElementById(element).style.display = "none"
                    }
                  });
              }

              function aire_modo(){
                if (modo < 3){
                    modo++
                } else {
                    modo = 0
                }
                document.getElementById("modo").innerHTML = modos[modo]
              }

              function aire_power(){
                estado = !estado
                if (estado){
                    document.getElementById("estado").innerHTML = 'PRENDIDO'
                } else {
                    document.getElementById("estado").innerHTML = 'APAGADO'
                }
              }

              function aire_temp(sentido){
                if (sentido == 'up' && temperatura < 30){
                    temperatura++
                } else if (sentido == 'down' && temperatura > 15){
                    temperatura--
                }
                document.getElementById("temp").innerHTML = temperatura
              }

              function aire_vel(){
                if (velocidad < 3){
                    velocidad++
                } else {
                    velocidad = 0
                }
                document.getElementById("vel").innerHTML = velocidades[velocidad]
              }

              function aire_swing(){
                swing = !swing
                if (swing){
                    document.getElementById("swing").innerHTML = 'SI'
                } else {
                    document.getElementById("swing").innerHTML = 'NO'
                }
              }

              function send_command(id){
                 const http = new window.XMLHttpRequest();
                 //http.open('POST','http://192.168.0.110/command',true);
                 http.open('POST', window.location.href + 'command',true);
                 http.setRequestHeader("Content-Type", "application/json");
                 var data = {dispositivo: device, id: id};
                 console.log(data);
                 http.send(JSON.stringify(data));
              }

              function send_state(){
                const http = new window.XMLHttpRequest();
                 //http.open('POST','http://192.168.0.110/state',true);
                 http.open('POST', window.location.href + 'state',true);
                 http.setRequestHeader("Content-Type", "application/json");
                 var data = {dispositivo: device, estado: estado, modo: modo, temperatura: temperatura, velocidad: velocidad, swing: swing};
                 console.log(data);
                 http.send(JSON.stringify(data));
              }
          </script>
      </body>
  </html>
)=====";
