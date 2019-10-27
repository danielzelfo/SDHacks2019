//*
//include ESP8266 library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const int LIGHT_SENSOR = 0;

void setup() {
  
  Serial.begin(9600);
  WiFi.begin("Adam's Pixel 3 XL", "Adamisawesome231985");   //WiFi connection


  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("Waiting for connection");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected"); 
  }
  int sensorValue = analogRead(A0);   // read the input on analog pin 0
  Serial.print("Light Sensor Value: ");
  Serial.println(sensorValue);
  delay(500);
  // put your main code here, to run repeatedly:
  if (WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    StaticJsonDocument<300> JSONDocument;   //Declaring static JSON buffer

    Serial.println(sensorValue);   // print out the value you read

    JSONDocument["device"] = "photo resistor";
    JSONDocument["sensor"] = "light";
    JSONDocument["value"] = sensorValue;
    char JSONmessageBuffer[300];
    
    Serial.println();
    Serial.print("serializeJson: ");
    serializeJson(JSONDocument, Serial);
    Serial.println();
    Serial.println();
    HTTPClient http;    //Declare object of class HTTPClient

    http.begin("http://danielzelfo.pythonanywhere.com/sensor");      //Specify request destination
    //http.begin("http://mtsacsdhacks.epizy.com/sensor/index.php"); 
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    serializeJson(JSONDocument, JSONmessageBuffer);
    Serial.println(JSONmessageBuffer);
    Serial.println();
    
    //*
    int httpCode = http.POST(JSONmessageBuffer);//Send the request
    /*
    while(httpCode != 201) {
      httpCode = http.POST(JSONmessageBuffer);
      delay(1000);
    }
    */
    String payload = http.getString();                  //Get the response payload
    Serial.println();
    Serial.println("Code:");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println("Payload:");
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection
    //*//*
  }
  else {
    Serial.println("Error in WiFi connection");   
  }
}

void loop() {
  
}
/*
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include "light.h"

void setup() {
 
  Serial.begin(9600);
  WiFi.begin("Adam's Pixel 3 XL", "Adamisawesome231985");   //WiFi connection


  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("Waiting for connection");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected"); 
  }
  // Connect to HTTP server
  WiFiClient client;
  client.setTimeout(10000);
  if (!client.connect("arduinojson.org", 80)) {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("Connected!"));

  // Send HTTP request
  client.println(F("GET /example.json HTTP/1.0"));
  client.println(F("Host: arduinojson.org"));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    return;
  }
  
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Extract values
  Serial.println(F("Response:"));
  Serial.println(doc["sensor"].as<char*>());
  Serial.println(doc["time"].as<long>());
  Serial.println(doc["data"][0].as<float>(), 6);
  Serial.println(doc["data"][1].as<float>(), 6);

  // Disconnect
  client.stop();
}

void loop() {
  // not used in this example
}
*/
