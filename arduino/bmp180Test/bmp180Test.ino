#include <EEPROM.h>
#include <Wire.h>
#include <SFE_BMP180.h>

/*
 * LUFTDRUCK MESSUNG mit speicherung im EPROM (Arduino 1024 Bytes)
 * niedrigster Luftdruck: 870 hPa (12.10.1979 im Taifun Tip, Guam Nordwestpazifik), stärkster Abfall: in 24h 98hPa 2005 Hurrikan Wilma, 882hPa
 * höchster Luftdruck: 1084hPa in Mongolei, 1060 hPa 1907 in Greifswald Deutschland)
 * => nehme 850 als 0 Punkt und speichere differenz dazu in bytes im EEprom, die letzten 4 (251-254) als Steuercodes, 255 ist meist initialwert, eventuel auch 0 ?
 * 254 = Programmstart, anschließend 4 Bytes Jahr Monat Tag Stunde, dann stündlich ein Wert => komme ca 42 Tage aus
 * EEProm (0)=Low Byte aktueller Zähler
 * EEProm (1)=High Byte aktueller Zähler
 * bei Programmstart erhöhe Zähler um 1 und schreibe aktuelles Datum und Uhrzeit rein (von Serieller lesen)
 */

SFE_BMP180 bmp180;
float alt = 400; // Altitude of current location in meters
int DruckNullPunkt=850;

int led = 13; // Pin 13 has an LED connected on most Arduino boards.
int blinkCount=0;

int eepromAdr=1; // die ersten 2 Bytes sind für den Adresszähler reserviert, vor erstem Schreiben wird der Zähler erhöht
byte low,hi;

void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
  digitalWrite(led, HIGH);

  low = EEPROM.read(0);
  hi = EEPROM.read(1);
  eepromAdr = low +hi*256;
  /*
  Serial.print("EEpromAdr:"  );
  Serial.println(eepromAdr);
  */
  Serial.println("InitBMP180");
  bool success = bmp180.begin();
  if (success) {
    Serial.println("BMP180initSuccess");
  }
  else {
    Serial.println("BMP180initFailure !");
  }

  
}

void loop() {

  BlinkLed();

  int serInByte=Serial.read();
  if (serInByte>0)
  {
    Serial.println();
    Serial.print("Eeprom Länge:");
    Serial.print(EEPROM.length());
    Serial.println(" ----------------------------------------------");
    int valCounter=0;
    for (int i=0; i<=EEPROM.length();i++)
    {
      int valEEprom=EEPROM.read(i);
      valEEprom=valEEprom+DruckNullPunkt;
      Serial.print(valEEprom);
      Serial.print(" ");
      valCounter=valCounter+1;
      if (valCounter>=24)
      {
        valCounter=0;
        Serial.println();
      }
    }
    Serial.println();
    Serial.println(" ----------------------------------------------");
    Serial.println();
  }

  ReadBmp();

}

void ReadBmp()
{
    char status;
  double T, P, seaLevelPressure, preasurePa;
  bool success = false;
  
  status = bmp180.startTemperature();

  if (status != 0) 
  {
    delay(2000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          seaLevelPressure = bmp180.sealevel(P, alt);
          byte preasureDiff=(byte)(seaLevelPressure-DruckNullPunkt);
          WriteEEProm(preasureDiff);
          
          preasurePa=seaLevelPressure/100;
          Serial.print("PressureAtSeaLevel[Pa]: ");
          Serial.print(preasurePa);
          Serial.print(", Temperature[°C]: ");
          Serial.print(T);
          /*
          Serial.print(" Diff:");
          Serial.print(preasureDiff);
          Serial.print(" eepromAdr:");
          Serial.print(eepromAdr);
          */
          Serial.println();
        }
      }
    }
  }
}

void WriteEEProm(byte val)
{
    eepromAdr=eepromAdr+1; //niemals drüberschreiben
    EEPROM.write(eepromAdr, val);
    if (eepromAdr == EEPROM.length()) 
    {
      eepromAdr = 1; //ersten 2 Bytes für den Adresszähler, wird ja erhöt vor dem 1. Mal schreiben
    }
    low = lowByte(eepromAdr);
    hi = highByte(eepromAdr);
    EEPROM.write(0, low);
    EEPROM.write(1, hi);
}

void BlinkLed()
{
  blinkCount = blinkCount +1;
  if (blinkCount>0)
  {
    blinkCount=0;
    
    int ledValue=digitalRead(led);
    digitalWrite(led, !ledValue);
    //Serial.print("Led:");
    //Serial.println(!ledValue);
    
  }
}
