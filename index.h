const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>           
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Sensor Value:<span id="ADCValue">0</span></h1><br>
  <br><a href="https://circuits4you.com">Circuits4you.com</a>
</div>

  <button type="button" id="Button1" onclick="change();" >LED ON</button>
  <button type="button" onclick="sendData(0)">LED OFF</button>
  <div>
  LED State is : <span id="LEDState">NA</span>
</div>
<script>

// ho creato una variabile per poter utilizzare un solo bottone per cambiare stato accesso spento di un led,
//il problema è che così la scritta sul bottone cambia, mentre
//il led potrebbe non essere acceso, per il fatto che la connessione fallisce
 var x = false;

function change() {

  if (x == false) {
    document.getElementById("Button1").innerHTML='LED OFF '; sendData(1);
    x = true;
  }else {
    document.getElementById("Button1").innerHTML='LED ON '; sendData(0); 
    x = false;
  }
}

// questa funzione serve a inviare un bit tra 0 e 1 per accendere il led
// non hoh ancora capito la scringa xhttp.open("GET", "setLED?LEDstate="+led)
function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true); // questa stringa non l'ho ancora capita,
  xhttp.send();                                     // perchè in genere il metodo "GET" si usa per inviare dati 
  
}
 // da qui in giù, serve per leggere un potenziometro
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
