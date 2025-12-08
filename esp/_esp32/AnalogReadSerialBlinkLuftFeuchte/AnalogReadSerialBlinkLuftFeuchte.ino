/*
benötigt DHT11 library
*/

#include <DHT11.h>

DHT11 dht11(4); //Init param=Pin Nr, esp32 2

#define led 2 //BUILTIN_LED

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  readTemp();
  readHum();

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  Serial.println("Led high");
  digitalWrite(led, HIGH);
  delay(250);  // delay in between reads for stability

  Serial.println("Led Low");
  digitalWrite(led, LOW);
  delay(250);  // delay in between reads for stability


}

void readTemp()
{
    Serial.print("try Temperature ...");
    int temperature = dht11.readTemperature();

    // Check the result of the reading.
    // If there's no error, print the temperature value.
    // If there's an error, print the appropriate error message.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(temperature));
    }
}

void readHum()
{
    Serial.print("try Humidity ...");
  int humidity = dht11.readHumidity();
  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
  } else {
      // Print error message based on the error code.
      Serial.println(DHT11::getErrorString(humidity));
  }
}


