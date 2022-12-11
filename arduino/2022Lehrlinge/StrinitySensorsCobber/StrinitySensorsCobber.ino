#include <AM2321.h>
#include <BMP180MI.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  AM2321 am;
  am.read();
  Serial.print("Temperatur: ");
  Serial.println(am.temperature / 10.0);
  Serial.print("Feuchtigkeit: ");
  Serial.println(am.humidity / 10.0);
  delay(1000);
}
