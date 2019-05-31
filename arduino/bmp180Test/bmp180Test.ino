#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;
float alt = 5.0; // Altitude of current location in meters


int led = 13; // Pin 13 has an LED connected on most Arduino boards.
bool ledHigh=true;

void setup() 
{
  Serial.begin(9600);
  bool success = bmp180.begin();

  if (success) {
    Serial.println("BMP180 init success");
  }
  else {
    Serial.println("BMP180 init failure !");
  }
}

void loop() {
  char status;
  double T, P, seaLevelPressure;
  bool success = false;

  status = bmp180.startTemperature();

	if (ledHigh)
	{
	  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
	}
	else
	{
	  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    }
    ledHigh = !ledHigh;
  
  if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          seaLevelPressure = bmp180.sealevel(P, alt);

          Serial.print("Pressure at sea level: ");
          Serial.print(seaLevelPressure);
          Serial.println(" hPa");
		  
		  Serial.print("Temperature: ");
          Serial.print(T);
          Serial.println(" °C");
        }
      }
    }
  }
}
