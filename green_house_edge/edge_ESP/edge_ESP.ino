#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h"   //pagina HTML contenente il javascript
#include "DHTesp.h"  //DHT11 library per ESP

#define LED 2        //LED on board
#define DHTpin 2    //D4 dell'ESP --> GPIO14

DHTesp dht;

//SSID and Password of WiFi router
// const char* ssid = "Infostrada-2.4GHz-DBB628";  //vale's WiFi
const char* ssid = "Alice Obelix";                 //rosso's WiFi
// const char* password = "3206528191569930";
const char* password = "timecapsule";

ESP8266WebServer server(80); //Server port -> 80

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page -> vd. SPIEGAZIONE
}

float humidity, temperature;

void handleADC() {
 int a = analogRead(A0);

 String data = "{\"ADC\":\""+String(a)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}"; //ADC -> Analog to Digital Converter
// data will be parsed to use it as javaScript's object in the webpage
 digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
 server.send(200, "text/plane", data); //Send ADC value, temperature and humidity to client

 //Get Humidity/temperatue data after request is complete
 //Give enough time to handle client request
  delay(dht.getMinimumSamplingPeriod());

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  Serial.print("\nUmidità: ");
  Serial.print(humidity);
  Serial.print("\nTemperatura: ");
  Serial.print(temperature);
  //Serial.print(dht.toFahrenheit(temperature)); print Fahrenheit temperature, if it's needed
}


void setup() {
  Serial.begin(115200);
  Serial.println();

  // use this instead:
  dht.setup(DHTpin, DHTesp::DHT11); //Connect DHT sensor DHTpin

  WiFi.begin(ssid, password);     //Connect to WiFi router
  Serial.println("\n");

  //Onboard LED port Direction output
  pinMode(LED,OUTPUT);

  // Wait for connection
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

  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readADC", handleADC); //This page is called by java Script AJAX --> it is taken by GET method

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();          //Handle client requests
}


/************************************************
SPIEGAZIONE:
send(String code, String content-Type, String message) //crea l'header del messaggio http
    code: rappresenta il codice di stato http - 200 è il codice standard per le richieste HTTP andate a buon fine
    content-Type: indica il media type della risorsa da inviare
    message: rappresenta il dato da inviare, questa è l'unico attributo che non è contenuto all'interno dell'header del messaggio http

Il metodo handleRoot manda un messaggio al client che effettua la richiesta. Il messaggio in questione è la pagina html (contenente anche alcuni script in js)
che deve essere mostrata nel frontend

Il metodo handleADC manda al frontend un messaggio HTTP contenente tutte le informazioni che gli interessano, ovvero la temperatura (°C) e l'umidità (%)



Con la funzione on() vengono gestite le richieste GET e POST:
i seguenti esempi sono equivalenti:

http://<ip address>/led?state=on  --> led ON --> accende il led
http://<ip address>/led?state=off --> led OFF --> spegne il led

server.on("/led", []() {
  String state=server.arg("state");
  if (state == "on") digitalWrite(13, LOW);
  else if (state == "off") digitalWrite(13, HIGH);
  server.send(200, "text/plain", "Led is now " + state);
});

*************************************************/
