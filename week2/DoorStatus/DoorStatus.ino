#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTTYPE     DHT22
#define DHTPIN      D5
#define ledPin      D7
#define pin_switch1 D1
#define pin_switch2 D2

#define WLAN_SSID     "xxxxxx"
#define WLAN_PASSWORD "xxxxxx"

DHT dht(DHTPIN, DHTTYPE, 11);

ESP8266WebServer server(80);

float temperature, humidity;
unsigned long previousMillis = 0;
const long interval = 2000;

String switch1Staus;
String switch2Staus;
String webString;
String ipaddress;

const char * ledtogglepage = "<!DOCTYPE html>"
"<html>"
"<body>"
"<p>NodeMCU-ESP8266 AJAX eksempel</p> "
"<button id=\"btnled\" onclick=\"ledtoggle()\">Klikk</button> "
"<script>"

"document.addEventListener(\"DOMContentLoaded\", function() {"
"  ledstatus();"
"});"

"setInterval(ledstatus, 1000);"

"function ledtoggle() {"
"  var xhttp = new XMLHttpRequest();"
"  xhttp.onreadystatechange = function() {"
"    if (this.readyState == 4 && this.status == 200) {"
"       console.log(this.responseText);"
"       if (this.responseText == 'Led: low') {"
"          document.getElementById(\"btnled\").innerHTML = 'LED er av, klikk for a sla den pa';"
"       } else {"
"          document.getElementById(\"btnled\").innerHTML = 'LED er pa, klikk for a sla den av';"
"       }"
"    }"
"  };"
"  xhttp.open('GET', '/led?state=toggle', true);"
"  xhttp.send(null);"
"  xhttp.timeout = 2000;"
"}"

"function ledstatus() {"
"  var xhttp = new XMLHttpRequest();"
"  xhttp.onreadystatechange = function() {"
"    if (this.readyState == 4 && this.status == 200) {"
"       console.log(this.responseText);"
"       if (this.responseText == 'Led: low') {"
"          document.getElementById(\"btnled\").innerHTML = 'LED er av, klikk for a sla den pa';"
"       } else {"
"          document.getElementById(\"btnled\").innerHTML = 'LED er pa, klikk for a sla den av';"
"       }"
"    }"
"  };"
"  xhttp.open('GET', '/led?state=status', true);"
"  xhttp.send(null);"
"  xhttp.timeout = 2000;"
"}"

"</script>"
"</body> "
"</html> ";


void setup() {
    WiFi.hostname( "Switch_Staus" );
  
    Serial.begin(115200);
    delay(50);

    pinMode(pin_switch1, INPUT_PULLUP);
    pinMode(pin_switch2, INPUT_PULLUP);

    pinMode(ledPin, OUTPUT);
    
    Serial.println("");
    Serial.println("");
    Serial.print("Kobler til ");
    Serial.println(WLAN_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("WiFi er tilkoblet");
    Serial.println("IP adresse: ");
    ipaddress = WiFi.localIP().toString();
    Serial.println(ipaddress);

    dht.begin();

    server.on("/ajax", HTTP_GET, [](){
        Serial.println("Klient ber om AJAX side");
        server.send(200, "text/html", ledtogglepage);
    });

 
    server.on("/", HTTP_GET, [](){
        getdht22status();
        getswitchstatus();
          
        webString = "Luftfuktighet " + String((int)humidity) + "%   Temperatur: " + String((int)temperature) + " C<br>" + "Status bryter 1: " + switch1Staus  + "<br>" + "Status bryter 2: " + switch2Staus;
               
        Serial.println(webString);
        server.send(200, "text/html", webString);
    });
    
    server.on("/doorstatus.json", [](){

        getswitchstatus();
        getdht22status();
        
        StaticJsonBuffer<500> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["temperature"] = temperature;
        root["humidity"] = humidity;
        root["switch1"] = switch1Staus;
        root["switch2"] = switch2Staus;
        
        String jsonString;
        root.printTo(jsonString);

        Serial.println(jsonString);
        server.send(200, "application/json", jsonString);
    });

    server.on("/led", led);  
    
    server.begin();
    Serial.println("WEB Server startet!");
    Serial.println("Klienter kan koble seg opp til:");
    Serial.println("http://" + ipaddress + "/index.html");
    Serial.println("http://" + ipaddress + "/doorstatus.json");
    Serial.println("http://" + ipaddress + "/led?state=on");
    Serial.println("http://" + ipaddress + "/led?state=off");
    Serial.println("http://" + ipaddress + "/led?state=toggle");
    Serial.println("http://" + ipaddress + "/ajax");
}

void loop() {
  server.handleClient();
}

void led(){
  String state=server.arg("state");
  String ledstatus;
  if (state == "on"){
    digitalWrite(ledPin, HIGH);
  } else if (state == "off"){
    digitalWrite(ledPin, LOW);
  } else if (state == "toggle"){
    if (digitalRead(ledPin) == HIGH){
      digitalWrite(ledPin, LOW);
      ledstatus = "low";
    } else {
      digitalWrite(ledPin, HIGH);
      ledstatus = "high";
    }
  } else if (state == "status"){
    if (digitalRead(ledPin) == LOW){
      ledstatus = "low";
    } else {
      ledstatus = "high";
    }
  }
    
  server.send(200, "text/plain", "Led: " + ledstatus );
}

void getswitchstatus(){
   if (digitalRead(pin_switch1) == LOW) {
     switch1Staus = "Apen";
   } else {
     switch1Staus = "Stengt";
   }

   if (digitalRead(pin_switch2) == LOW) {
     switch2Staus = "Apen";
   } else {
     switch2Staus = "Stengt";
   }
}

void getdht22status(){
  if ( millis() - previousMillis >= interval) {
    previousMillis = millis();

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Feil fra DHT sensor!");
      return;
    }
  }
}


