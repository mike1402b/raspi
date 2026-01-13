/*
benötigt adafruit bmp085 Library, geht auch für bmp180
https://randomnerdtutorials.com/esp32-with-bmp180-barometric-sensor/
*/

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

#define led 2 //BUILTIN_LED

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
	while (1) {}
  }
}

// the loop routine runs over and over again forever:
void loop() {

   Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  Serial.println("Led high");
  digitalWrite(led, HIGH);
  delay(250);  // delay in between reads for stability

  Serial.println("Led Low");
  digitalWrite(led, LOW);
  delay(250);  // delay in between reads for stability


}

