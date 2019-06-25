/********************************************
Quest'altro file nasce dal fatto che non sono sicuro che l'altra versione vada bene al prof,
dato che esp si comporta come un server, attendendo le richieste di JavaServer, per poi mandargli le informazioni.

Qui le informazioni vengono mandate e bona
*******************************************/

// #include <ESP8266WiFi.h>
// #include "DHTesp.h"  //DHT11 library per ESP
//
// #define LED 2        //LED on board
// #define DHTpin 2    //D4 dell'ESP --> GPIO14
//
//
// DHTesp dht;
//
// //SSID and Password of WiFi router
// // const char* ssid = "Infostrada-2.4GHz-DBB628";  //vale's WiFi
// // const char* ssid = "Alice Obelix";              //rosso's WiFi
// const char* ssid = "AndroidHotspot3965L";         //rosso's hotspot
//
// // const char* password = "3206528191569930";      //vale's WiFi
// // const char* password = "timecapsule";           //rosso's WiFi
// const char* password = "totocutugno";
//
// float humidity, temperature;
// const char* host = "192.168.43.1";  //Server IP
// const int   port = 8080;            //Server Port
// const int   watchdog = 5000;        //Watchdog frequency
// unsigned long previousMillis = millis();
//
//
// void handleADC() {
//  int a = analogRead(A0); //digitalRead
//
//  String data = "{\"ADC\":\""+String(a)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}"; //ADC -> Analog to Digital Converter
// // data will be parsed to use it as javaScript's object in the webpage -> JSON
//  digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
//  //server.send(200, "text/plane", data); //Send ADC value, temperature and humidity to client
//
//  //Get Humidity/temperatue data after request is complete
//  //Give enough time to handle client request
//   delay(dht.getMinimumSamplingPeriod());
//
//   humidity = dht.getHumidity();
//   temperature = dht.getTemperature();
//
//   Serial.print("\nUmidità: ");
//   Serial.print(humidity);
//   Serial.print("\nTemperatura: ");
//   Serial.print(temperature);
//   //Serial.print(dht.toFahrenheit(temperature)); print Fahrenheit temperature, if it's needed
// }
//
// void setup() {
//   Serial.begin(115200);
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//
//   dht.setup(DHTpin, DHTesp::DHT11); //Connect DHT sensor DHTpin
//
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }
//
// void loop() {
//   unsigned long currentMillis = millis();
//
//   if ( currentMillis - previousMillis > watchdog ) {
//     previousMillis = currentMillis;
//     WiFiClient client;
//
//     if (!client.connect(host, port)) {
//       Serial.println("connection failed");
//       return;
//     }
//
//     // This will send the request to the server
//     client.print(String("GET ") + "/ HTTP/1.1\r\n" +
//                "Host: " + host + ":" + String(port) + "\r\n" +
//                "Connection: keep-alive\r\n\r\n");
//     unsigned long timeout = millis();
//     while (client.available() == 0) {
//       if (millis() - timeout > 5000) {
//         Serial.println(">>> Client Timeout !");
//         client.stop();
//         return;
//       }
//     }
//
//     // Read all the lines of the reply from server and print them to Serial
//     while(client.available()){
//       String line = client.readStringUntil('\r');
//       Serial.print(line);
//     }
//   }
// }
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <DHTesp.h>

#define DHT_PIN 2    //D4 dell'ESP --> GPIO14

const char* ssid = "AndroidHotspot3965L";         //rosso's hotspot
const char* password = "totocutugno";         //rosso's hotspot
const char* address = "http://9a924b8a.ngrok.io";
const int port = 8080;
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
    http.begin(address + "/api/humidity");
    http.addHeader("Content-Type", "application/json");
    String msg =
        String("{ \"value\" ") + String(value) + "\" }";
    Serial.println(msg);

    int retCode = http.POST(msg);
    http.end();

    String payload = http.getString();
    Serial.println(payload);
    return retCode;
}

void loop() {
    if (WiFi.status()== WL_CONNECTED){
      int humidity = analogRead(DHT_PIN);
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
    delay(2000);
}
