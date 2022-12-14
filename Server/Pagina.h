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
                padding: 15px 28px;
                text-align: center;
                display: inline-block;
                font-size: 16px;
            }

            button:disabled,
            button[disabled]{
                border: 1px solid #999999;
                background-color: #cccccc;
                color: #666666;
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
                padding-left: 0px;
                padding-top: 6px;
                padding-right: 0px;
                padding-bottom: 6px;
                margin:auto;
            }

            .fila {
                display: flex;
            }

            .b2 {
                width: 50%;
            }

            .b3 {
                width: 33.33%;
            }

            .columna {
                flex: 50%;
            }

            select, select:focus, optgroup {
                width: 400px;
                height: 30px;
                color: white;
                border-color: black;
                color: #000;
                border-radius: 5px;
            }

        </style>
        <body onload="init()">
            <div style="text-align: center;">
                <h1>Clonador de Controles Infrarrojos</h1>
            </div>
            <div>
                <div class="row">
                    <div class="col">
                        <button id="tv_button" class="button" onclick="display('televisor')">Television</button>
                    </div>
                    <div class="col">
                        <button id="ac_button" class="button" onclick="display('aire')">Aire Acondicionado</button><BR>
                    </div>
                    <div class="col">
                        <button id="proy_button" class="button" onclick="display('proyector')">Proyector</button><BR>
                    </div>
                </div>
            </div><br><hr>
            <div id="televisor"  style="display:none;">
                <div class="row centrar" >
                    <div class="col centrar">
                        <label>Seleccione TV</label>
                        <select id="televisores" onchange="changeDevice('televisores')">
                            <option value="tv_tcl">TCL</option>
                            <option value="tv_jvc">JVC</option>
                            <option value="tv_sony">Sony</option>
                        </select>
                    </div>
                </div>
                <hr>
                <div class="row centrar">
                    <div class="col  centrar" >
                        <button class="button" style="background-color: #f32c2c" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b2" onclick="send_command(buttons['CHANNEL_UP'])">CANAL +</button>
                        <button class="button b2" onclick="send_command(buttons['CHANNEL_DOWN'])">CANAL -</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b2" onclick="send_command(buttons['VOLUME_UP'])">VOL +</button>
                        <button class="button b2" onclick="send_command(buttons['VOLUME_DOWN'])">VOL -</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button" onclick="send_command(buttons['UP'])"><span id="f_arriba_tv"></span></button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['LEFT'])"><span id="f_izquierda_tv"></span></button>
                        <button class="button b3" onclick="send_command(buttons['ACCEPT'])">OK</button>
                        <button class="button b3" onclick="send_command(buttons['RIGHT'])"><span id="f_derecha_tv"></span></button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button" onclick="send_command(buttons['DOWN'])"><span id="f_abajo_tv"></span></button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b2" onclick="send_command(buttons['HOME'])">HOME</button>
                        <button class="button b2" onclick="send_command(buttons['MUTE'])">MUTE</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b2" onclick="send_command(buttons['BACK'])">BACK</button>
                        <button class="button b2" onclick="send_command(buttons['CONFIGURATION'])">CONF</button>
                    </div>
                </div>
            </div>
            <div id="aire" style="display:none;">
                <div class="row centrar" style="display:none;">
                    <div class="col centrar">
                        <label>Seleccione Aire</label>
                        <select id="airees" onchange="changeDevice('airees')">
                            <option value="aire">Aire Coolix</option>
                        </select>
                    </div>
                </div>
                <hr>
                <div class="fila">
                    <div class="columna">
                        <div class="row centrar">
                            <div class="col  centrar" >
                                <button class="button" style="background-color: #f32c2c" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <button class="button" onclick="send_command(buttons['MODE'])">MODO</button>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <button class="button b2" onclick="send_command(buttons['TEMP_UP'])">TEMP+</button>
                                <button class="button b2" onclick="send_command(buttons['TEMP_DOWN'])">TEMP-</button>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <button class="button b2" onclick="send_command(buttons['FAN'])">VELOCIDAD</button>
                                <button class="button b2" onclick="send_command(buttons['SWING'])">SWING</button>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <button class="button" onclick="send_command(buttons['LED'])">LED</button>
                            </div>
                        </div>
                    </div>
                    <div class="columna">
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>Power: <span id="power"></span></h2>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>Modo: <span id="mode"></span></h2>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>Temperatura: <span id="temp"></span><span id="grados"></span></h2>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>Velocidad: <span id="fan"></span></h2>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>Swing: <span id="swing"></span></h2>
                            </div>
                        </div>
                        <div class="row centrar">
                            <div class="col centrar">
                                <h2>LED: <span id="led"></span></h2>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div id="proyector"  style="display:none;">
                <div class="row centrar" style="display: none;">
                    <div class="col centrar">
                        <label>Seleccione Proyector</label>
                        <select id="proyectores" onchange="changeDevice('proyectores')">
                            <option value="proyector">Proyector Facultad</option>
                        </select>
                    </div>
                </div>
                <hr>
                <div class="row centrar">
                    <div class="col  centrar" >
                        <button class="button b3" style="background-color: #f32c2c" onclick="send_command(buttons['POWER'])">ON/OFF</button>
                        <button class="button b3" onclick="send_command(buttons['SOURCE'])">SOURCE</button>
                        <button class="button b3" onclick="send_command(buttons['HELP'])">HELP</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['MENU'])">MENU</button>
                        <button class="button b3" onclick="send_command(buttons['UP'])"><span id="f_arriba_p"></span></button>
                        <button class="button b3" onclick="send_command(buttons['BACK'])">BACK</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['LEFT'])"><span id="f_izquierda_p"></span></button>
                        <button class="button b3" onclick="send_command(buttons['ACCEPT'])">OK</button>
                        <button class="button b3" onclick="send_command(buttons['RIGHT'])"><span id="f_derecha_p"></span></button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['AUTO'])">AUTO</button>
                        <button class="button b3" onclick="send_command(buttons['DOWN'])"><span id="f_abajo_p"></span></button>
                        <button class="button b3" onclick="send_command(buttons['VOLUME'])">VOLUME</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['PAGE_UP'])">PAGE+</button>
                        <button class="button b3" onclick="send_command(buttons['ZOOM_IN'])">ZOOM+</button>
                        <button class="button b3" onclick="send_command(buttons['FREEZE'])">FREEZE</button>
                    </div>
                </div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button class="button b3" onclick="send_command(buttons['PAGE_DOWN'])">PAGE-</button>
                        <button class="button b3" onclick="send_command(buttons['ZOOM_OUT'])">ZOOM-</button>
                        <button class="button b3" onclick="send_command(buttons['MUTE'])">MUTE A/V</button>
                    </div>
                </div>
            </div>
            <hr>
            <div>
                <div class="row centrar">
                    <div class="col centrar">
                        <button id="chmod_butt" class="button" onclick="change_mode()" style="background-color: #eb9502;">PASAR A LECTURA DE TRAMAS</button>
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
                    1 : 'HUMEDAD',
                    2 : 'AUTO',
                    3 : 'CALOR'
                }

                const velocidades = {
                    0 : 'AUTOMATICA',
                    1 : 'BAJA',
                    2 : 'MEDIA',
                    3 : 'ALTA'
                }

                const on_off = {
                    true : 'ON',
                    false : 'OFF'
                }

                const controles = ['televisor','aire','proyector']

                const botones = ['tv_button','ac_button','proy_button']

                const grados = '%C2%B0C'
                const f_izquierda = '%E2%86%90'
                const f_arriba = '%E2%86%91'
                const f_derecha = '%E2%86%92'
                const f_abajo = '%E2%86%93'

                var device

                var modo_lectura = false

                function init(){
                    document.getElementById("f_izquierda_tv").innerHTML = decodeURI(f_izquierda)
                    document.getElementById("f_arriba_tv").innerHTML = decodeURI(f_arriba)
                    document.getElementById("f_derecha_tv").innerHTML = decodeURI(f_derecha)
                    document.getElementById("f_abajo_tv").innerHTML = decodeURI(f_abajo)

                    document.getElementById("grados").innerHTML = decodeURI(grados)

                    document.getElementById("f_izquierda_p").innerHTML = decodeURI(f_izquierda)
                    document.getElementById("f_arriba_p").innerHTML = decodeURI(f_arriba)
                    document.getElementById("f_derecha_p").innerHTML = decodeURI(f_derecha)
                    document.getElementById("f_abajo_p").innerHTML = decodeURI(f_abajo)
                    
                }

                function display(id) {
                    controles.forEach(element => {
                        if (element == id){
                            document.getElementById(element).style.display = "block"
                            changeDevice(id+'es') //plural del control
                        } else {
                            document.getElementById(element).style.display = "none"
                        }
                    });
                }

                function changeDevice(arg) {
                    device = document.getElementById(arg).value
                }

                function send_command(id){
                    const http = new window.XMLHttpRequest()
                    http.open('POST', window.location.href + 'command',true)
                    http.onreadystatechange = function() {
                        if (device == 'aire' && this.readyState == 4 && this.status == 200) {
                            let status = JSON.parse(this.responseText)
                            update_status(status)
                        }
                    }
                    http.setRequestHeader("Content-Type", "application/json")
                    var data = {dispositivo: device, id: id}
                    console.log(data)
                    http.send(JSON.stringify(data))
                }

                function update_status(status){
                    document.getElementById("mode").innerHTML = modos[status.mode]
                    document.getElementById("fan").innerHTML = velocidades[status.fan]
                    document.getElementById("power").innerHTML = on_off[status.power]
                    document.getElementById("led").innerHTML = on_off[status.led]
                    document.getElementById("swing").innerHTML = on_off[status.swing]
                    document.getElementById("temp").innerHTML = status.temp
                }

                function change_mode(){
                    const http = new window.XMLHttpRequest()
                    http.onreadystatechange = function() {
                        if (this.readyState == 4 && this.status == 200) {
                            if (!modo_lectura){
                                controles.forEach(element => {
                                    document.getElementById(element).style.display = "none"
                                });
                                botones.forEach(element => {
                                    document.getElementById(element).disabled = true
                                });
                                document.getElementById("chmod_butt").textContent = "PASAR A EMISION DE TRAMAS"
                                modo_lectura = true
                            } else {
                                botones.forEach(element => {
                                    document.getElementById(element).disabled = false
                                });
                                document.getElementById("chmod_butt").textContent = "PASAR A LECTURA DE TRAMAS"
                                modo_lectura = false
                            }
                        }
                    }
                    http.getResponseHeader("Content-type", "application/json")
                    http.open('GET', window.location.href + 'mode',true)
                    http.send()
                }
            </script>
        </body>
    </html>
)=====";
