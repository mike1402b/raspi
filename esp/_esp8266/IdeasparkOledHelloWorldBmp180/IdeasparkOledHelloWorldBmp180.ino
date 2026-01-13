/*



bmp180:
need Adafruit_BMP085 
https://www.hackster.io/theguyknowstech/how-to-interface-bmp180-module-with-esp8266-iotguru-cloud-c6bcf3
*/

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define SDA_PIN 12 //GPIO12 / 6
#define SCL_PIN 14 //GPIO14 / 5
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL_PIN, SDA_PIN, U8X8_PIN_NONE);

#define led 2 //BUILTIN_LED

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  u8g2.begin();

  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
	while (1) {}
  }

}

void OledWrite(String text)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,text.c_str());
  u8g2.sendBuffer();
}

// the loop routine runs over and over again forever:
void loop() {


  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  float temp=bmp.readTemperature();
  String tempStr=String(temp);
  String tempText="Temp="+tempStr+" *C";
  Serial.println(tempText);
  OledWrite(tempText);
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  int sensorValue = analogRead(A0);
  String text="Sensor="+String(sensorValue);
  Serial.println(text);
  //OledWrite(text);

  digitalWrite(led, HIGH);
  delay(250);  // delay in between reads for stability

  digitalWrite(led, LOW);
  delay(250);  // delay in between reads for stability


}



