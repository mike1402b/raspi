#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;
float alt = 5.0; // Altitude of current location in meters

void setup() 
{
  Serial.begin(9600);
  bool success = bmp180.begin();

  if (success) {
    Serial.println("BMP180 init success");
  }
}

void loop() {
  char status;
  double T, P, seaLevelPressure;
  bool success = false;

  status = bmp180.startTemperature();

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
        }
      }
    }
  }
}
