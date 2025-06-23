#include <WiFi.h>
#include <WebServer.h> 


const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    button { padding: 10px 20px; font-size: 16px; margin: 10px; }
  </style>
</head>
<body>
  <h1>ESP32 Web Interface</h1>
  <script>
  function sendSlider(val) {

    fetch("/slider?${val});
  }
  </script>
  <button onclick="fetch('/led/blue')">Led Azul</button>
  <button onclick="fetch('/led/red')">Led Vermelha</button>
  <button onclick="fetch('/led/green')">Led Verde</button>
  <button onclick="fetch('/led/off')">Desligar led</button>

  <p>Presets</p>
  <button onclick="fetch('/led/dance')">Dance</button>
  <button onclick="fetch('/led/vaporwave')">Vaporwave</button>
</body>
</html>
)rawliteral";



const char* ssid="wifi-ssid";
const char* password="password";
const int redPin = 23;
const int bluePin = 18;
const int greenPin = 19;

String activePreset = "";

WebServer server(80);


void printServer(){

  server.send(200, "text/html", htmlPage);
}




void offLed(){
activePreset = "";
digitalWrite(bluePin, LOW);
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
}
  

void blueLed(){
offLed();
digitalWrite(bluePin, HIGH);
}

void redLed(){
offLed();
digitalWrite(redPin, HIGH);
}

void greenLed(){
offLed();
digitalWrite(greenPin, HIGH);
}


void setup() {
  // put your setup code here, to run once:
pinMode(redPin, OUTPUT);
pinMode(bluePin, OUTPUT);
pinMode(greenPin, OUTPUT);
digitalWrite(redPin, HIGH);
Serial.begin(115200);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
{
Serial.println("...");
}

Serial.println(WiFi.localIP());

server.on("/", printServer);
server.on("/led/red", redLed);
server.on("/led/blue", blueLed);
server.on("/led/green", greenLed);
server.on("/led/off", offLed);

server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
