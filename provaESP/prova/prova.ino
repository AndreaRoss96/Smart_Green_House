// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <DHT.h>
//
// #define DHTPIN 2        // Digital pin D4
// #define DHTTYPE DHT11   // DHT 11
//
// DHT dht(DHTPIN, DHTTYPE);
// ESP8266WebServer server(80);    //Webserver Object
//
// const char * htmlMessage = "<!DOCTYPE html> "
// "<html> "
//     "<body> "
//         "<p>This is a HTML only intro page. Please select a button bellow.</p>"
//         "<a href=\"/javascript\">Javascript code</a>"
//         "</br>"
//         "<a href=\"/cssButton\">CSS code</a>"
// "   </body> "
// "</html> ";
//
// const char * javascriptCode = "<!DOCTYPE html>"
// "<html>"
//     "<body>"
//         "<p>Click the button to get a message from the ESP8266:</p>"
//         "<button onclick=\"buttonFunction()\">Message</button>"
//         "<script>"
//             "function buttonFunction() {"
//                 "alert(\"Hello from the ESP8266!\");"
//             "}"
//         "</script>"
//     "</body> "
// "</html>";
//
// const char * cssButton ="<!DOCTYPE html>"
// "<html>"
//     "<head>"
//     "<style>"
//     ".button {"
//         "background-color: #990033;"
//         "border: none;"
//         "color: white;"
//         "padding: 7px 15px;"
//         "text-align: center;"
//         "cursor: pointer;"
//     "}"
//     "</style>"
//     "</head>"
//     "<body>"
//         "<input type=\"button\" class=\"button\" value=\"Input Button\">"
//     "</body>"
// "</html>";
//
// void setup() {
//
//     Serial.begin(115200);                                             //Open Serial connection
//     dht.begin();
//     WiFi.begin("AndroidHotspot3965L", "totocutugno");                          //Connect to the WiFi network
//
//     while (WiFi.status() != WL_CONNECTED) {    //Wait for connection
//         delay(500);
//         Serial.println("Waiting to connect…");
//     }
//
//     Serial.print("IP address: ");
//     Serial.println(WiFi.localIP());  //Print the local IP
//
//     server.on("/html", []() {                     //Define the handling function for root path (HTML message)
//         server.send(200, "text/html", htmlMessage);
//     });
//
//     server.on("/javascript", []() { //Define the handling function for the javascript path
//         server.send(200, "text/html", javascriptCode);
//     });
//
//     server.on("/cssButton", []() { //Define the handling function for the CSS path
//         server.send(200, "text/html", cssButton);
//     });
//
//     server.begin(); //Start the server
//     Serial.println("Server listening");
// }
//
// void loop() {
//
//     server.handleClient(); //Handling of incoming requests
// }
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <string>

#define DHTPIN 2        // Digital pin D4
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to AndroidHotspot3965L");
  WiFi.begin("AndroidHotspot3965L", "totocutugno");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  dht.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

// prepare a web page to be send to a client (web browser)
String prepareHtmlPage() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
//nuovo codice da quando funziona
    float temperature = dht.computerHeatIndex(t, h, false); //false for celsius
    
    if (h != NULL || temperature != NULL) { //devono essere inizializzate la prima volta
      static float newHumidity = h;
      static float newTemperature = temperature;
    } 

    

    
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
                "<p style=\"color: red;\"> Temperature: " +  String(newTemperature) + "</p>"
                "<p style=\"color: blue;\"> Humidity: " + String(newHumidity) + "% </p>"
            "</html>" +
            "\r\n";
  return htmlPage;
}


void loop() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client) {
    Serial.println("\n[Client connected]");
    while (client.connected()) {
      // read line by line what the client (web browser) is requesting
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n') {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    delay(250); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
  }
}
