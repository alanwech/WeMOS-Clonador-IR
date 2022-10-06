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
              width: 40%;
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
              width: 500px;
              padding: 10px;
              margin:auto;
          }
  
      </style>
      <body>
          <div style="text-align: center;">
              <h1>Clonador de Controles Infrarrojos</h1>
          </div>
          <div class="container">
              <div class="row">
                  <div class="col">
                      <button class="button" onclick="display('tele')">Television</button>
                  </div>
                  <div class="col">
                      <button class="button" onclick="display('aire')">Aire Acondicionado</button><BR>
                  </div>
              </div>
          </div><br><hr><br>
          <div id="tele"  style="display:none;">
              <div class="row centrar">
                  <div class="col  centrar" >
                      <button class="button" style="background-color: #f32c2c" onclick="solicitud('tv','POWER')">ON/OFF</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="solicitud('tv','CHANNEL_UP')">CANAL +</button>
                      <button class="button" onclick="solicitud('tv','CHANNEL_DOWN')">CANAL -</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="solicitud('tv','VOLUME_UP')">VOL +</button>
                      <button class="button" onclick="solicitud('tv','VOLUME_DOWN')">VOL -</button>
                  </div>
              </div>
          </div>
          <div id="aire"  style="display:none;" class="container" >
              <div class="row centrar">
                  <div class="col  centrar" >
                      <button class="button" style="background-color: #f32c2c" onclick="solicitud('aire',0)">ON/OFF</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="solicitud('aire',1)">MODO</button>
                  </div>
              </div>
              <div class="row centrar">
                  <div class="col centrar">
                      <button class="button" onclick="solicitud('aire',2)">TEMP +</button>
                      <button class="button" onclick="solicitud('aire',3)">TEMP -</button>
                  </div>
              </div>
          </div>
          <script>
              function display(id) {
                  document.getElementById(id).style.display = "block";
                  if (id == 'tele'){
                      document.getElementById('aire').style.display = "none";
                  } else {
                      document.getElementById('tele').style.display = "none";
                  }
              }
              function solicitud(disp, id){
                 const http = new window.XMLHttpRequest();
                 http.open('POST','http://192.168.0.110/command',true);
                 http.setRequestHeader("Content-Type", "application/json");
                 var data = {dispositivo: disp, id: id};
                 console.log(data);
                 http.send(JSON.stringify(data));
              }
          </script>
      </body>
  </html>
)=====";
