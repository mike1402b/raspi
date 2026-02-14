/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

const char* ssid = "hew17";
const char* password = "Hew2549!";

//Your Domain name with URL path or IP address with path
String serverName = "http://t98.azurewebsites.net/zeitaddapi";
//String serverName = "https://localhost:5000/zeitaddapi";

// the following variables are unsigned longs because the time, measured in milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

#define builtinLed 2 //BUILTIN_LED
bool lastLed=true;

void setup() {
  pinMode(builtinLed, OUTPUT);
  digitalWrite(builtinLed, HIGH);

  Serial.begin(9600); 
  delay(500);
  Serial.println("======================================  setup  =========================================");

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());


  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
	while (1) {}
  }
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}


double oldTemp=-270;

void loop() {
  // Send an HTTP POST request depending on timerDelay
  int val=1;
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED)
    {

      double temp=bmp.readTemperature();

      Serial.print("Temperature = ");
      Serial.print(temp);
      Serial.println(" *C");
      
      Serial.print("Pressure = ");
      Serial.print(bmp.readPressure());
      Serial.println(" Pa");

      if (abs(oldTemp-temp)>0.1) // nur größere Änderungen als 0,1 °C schreiben
      {
        oldTemp=temp;

        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName + "?test=Ilmi14&status=0&val="+String(temp); //TODO kategorie parameter taskid übergeben
        //String serverPath="http://192.168.1.6/test1.html";
        val=val+1;
        Serial.print("serverPath=");
        Serial.println(serverPath);
        
        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
    
        // If you need Node-RED/server authentication, insert user and password below
        //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
          
        // Send HTTP GET request
        int httpResponseCode = http.GET();
        
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          //macht wenig sinn, da response sehr langer text aufgrund fehler in webanwendung Serial.println(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
      }
      
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }
    delay(1000);
    lastLed=!lastLed;
    if (lastLed)
      digitalWrite(builtinLed, HIGH);
    else
      digitalWrite(builtinLed, LOW);
    lastTime = millis();
  }
}