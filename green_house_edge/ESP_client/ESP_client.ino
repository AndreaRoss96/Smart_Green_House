/********************************************
Quest'altro file nasce dal fatto che non sono sicuro che l'altra versione vada bene al prof,
dato che esp si comporta come un server, attendendo le richieste di JavaServer, per poi mandargli le informazioni.

Qui le informazioni vengono mandate e bona
*******************************************/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <DHTesp.h>

#define DHT_PIN 2    //D4 dell'ESP --> GPIO14

const char* ssid = "AndroidHotspot3965L";         //rosso's hotspot
const char* password = "totocutugno";         //rosso's hotspot
const char* address = "http://f183e7da.ngrok.io";
/*const int port = 8080;*/
const int watchdog = 5000;
unsigned long previousMillis = millis();

ESP8266WiFiMulti wifiMulti;
HTTPClient http;
DHTesp dht;

void setup() {
    Serial.begin(115200);
    dht.setup(DHT_PIN, DHTesp::DHT11); //Connect DHT sensor DHTpin
    WiFi.begin(ssid, password);

    // Wait for connection
    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    //If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to ESP

    Serial.setDebugOutput(true);
}

int sendData(String address, float value, String label){
    HTTPClient http;
    http.begin(address + "/api/data");
    http.addHeader("Content-Type", "application/json");
    String msg = String(value);
        //String("{ value ") + String(value) + " }";
    Serial.println(msg);

    int retCode = http.POST(msg);
    http.end();

    String payload = http.getString();
    Serial.println(payload);
    return retCode;
}

void loop() {
    if (WiFi.status()== WL_CONNECTED){
      // int humidity = dht.getHumidity();
      // Variable for potentiometer below
      float sensorValue = analogRead(A0);
      float humidity = map(sensorValue, 0, 1023, 0, 100);
      Serial.println("Humidity: " + String(humidity));
      int code = sendData(address, humidity, "Humidity");
      /* log result */
      if (code == 200){
        Serial.println("ok");
      } else {
        Serial.println("error");
      }
    } else {
      Serial.println("Error in WiFi connection");
    }
    delay(10000);
}
