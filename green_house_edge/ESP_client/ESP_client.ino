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

const char* host = "192.168.43.144";
const char* ssid = "AndroidHotspot3965L";         //rosso's hotspot
const char* password = "totocutugno";         //rosso's hotspot
const int port = 8080;
const int watchdog = 5000;
unsigned long previousMillis = millis();

ESP8266WiFiMulti wifiMulti;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  wifiMulti.addAP(ssid, password);

  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.print(WiFi.localIP());
  }
  Serial.setDebugOutput(true);

}

int value = 0;

void loop() {
  unsigned long currentMillis = millis();

  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;

    if(wifiMulti.run() != WL_CONNECTED) {
      Serial.println("!!");
    } else {
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      String url = "/watchdog?command=watchdog&uptime=";
      url += String(millis());
      url += "&ip=";
      url += WiFi.localIP().toString();

      Serial.print("connecting to ");
      Serial.println(host);
      Serial.print("Requesting URL: ");
      Serial.println(url);

      http.begin(host,port,url);
      int httpCode = http.GET();
      if (httpCode) {
        if (httpCode == 200) {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      Serial.println("closing connection");
      http.end();
      WiFi.disconnect();
    }
  }
}
