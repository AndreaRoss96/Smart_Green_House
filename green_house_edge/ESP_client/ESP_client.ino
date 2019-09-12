#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHTesp.h>

#define DHT_PIN 2    //D4 dell'ESP --> GPIO14

char* ssid = "AndroidHotspot3965L";
char* password = "totocutugno";
char* address = "http://3645eaec.ngrok.io";

DHTesp dht;

void setup() { 
  Serial.begin(115200);         
  dht.setup(DHT_PIN, DHTesp::DHT11); //Connect DHT sensor DHTpin                       
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
   
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to ESP
}

int sendData(String address, float value){  
   HTTPClient http;    
   http.begin(address + "/api/data");      
   http.addHeader("Content-Type", "application/json");     
   String msg = 
   String("{\"Humidity\":") + String(value) + "}";
   int retCode = http.POST(msg);   
   http.end();  
   Serial.print(msg);
   return retCode;
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   
   // int humidity = dht.getHumidity();
   float sensorValue = analogRead(A0);
   int humidity = map(sensorValue, 0, 1023, 0, 100);
   /* send data */
   Serial.print("sending "+String(humidity)+"...");    
   int code = sendData(address, humidity);
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
