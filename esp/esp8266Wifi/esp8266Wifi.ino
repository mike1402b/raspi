
#include <ESP8266WiFi.h>


int pin = 2;
int i=0;

void setup() {
  // initialize GPIO 2 as an output.
  pinMode(pin, OUTPUT);
  Serial.begin(115200);  
  // Attempt to connect to a specific access point
  Serial.println("try connect to Wifi");
  WiFi.begin("Nokia X20", "xxxPwdxxx"); 
  Serial.println("finished Wifi.begin");
}

// the loop function runs over and over again forever

void loop() {

  i=i+1;
  if (i>100) i=0;
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
  }
  else
  {
    Serial.print(i);
    Serial.println(" wifi not connected");  
  }
}
