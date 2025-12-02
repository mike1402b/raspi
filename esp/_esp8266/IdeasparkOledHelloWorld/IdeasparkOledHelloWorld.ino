/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/

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

}

void OledWrite(String text)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"Hello World!");
  u8g2.sendBuffer();
}

// the loop routine runs over and over again forever:
void loop() {

  int sensorValue = analogRead(A0);
  String text="Sensor="+String(sensorValue);
  Serial.println(text);
  OledWrite(text);
  digitalWrite(led, HIGH);
  delay(250);  // delay in between reads for stability

  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  OledWrite(text);
  digitalWrite(led, LOW);
  delay(250);  // delay in between reads for stability


}



