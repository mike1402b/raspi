//needs PubSubClient Library ? and Arduino_JSON ?

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int pin = 2;
int i=0;

void setup() {
  // initialize GPIO 2 as an output.
  pinMode(pin, OUTPUT);
  Serial.begin(115200);  
  // Attempt to connect to a specific access point
  Serial.println("try connect to Wifi");
  WiFi.begin("Nokia X20", "Hew2549!"); 
  Serial.println("finished Wifi.begin");
}

// the loop function runs over and over again forever

void loop() {

  i=i+1;
  if (i>20) i=0;

  int sensorValue = analogRead(A0);
  Serial.print("Analog Value=");
  Serial.println(sensorValue);
  
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second
  if (WiFi.status() == WL_CONNECTED) 
  {
    Serial.print(i);
    Serial.print(" IP address: ");
    Serial.println(WiFi.localIP());
    if (i==1)
    {
        WiFiClient client;
        HTTPClient http;  //Declare an object of class HTTPClient
 
        http.begin(client,"http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
        int httpCode = http.GET();                                  //Send the request
     
        if (httpCode > 0) { //Check the returning code
     
          String payload = http.getString();   //Get the request response payload
          Serial.println(payload);             //Print the response payload
     
        }
     
        http.end();   //Close connection
    }
  }
  else
  {
    Serial.print(i);
    Serial.println(" wifi not connected");  
  }
}
