#include <EEPROM.h>
#include <Wire.h>
#include <TimeLib.h>
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

bool debug=false;

SFE_BMP180 bmp180;
float alt = 400; // Altitude of current location in meters
int DruckNullPunkt=850;
int bmpReadCounter=0; //alle x Schleifendurchläufe lesen

int led = 13; // Pin 13 has an LED connected on most Arduino boards.
int blinkCount=0;

//----------- EEprom ----------
int eepromDumpNewLineCounter=0; //EEprom NewLineCounter
int eepromAdr=1; // die ersten 2 Bytes sind für den Adresszähler reserviert, vor erstem Schreiben wird der Zähler erhöht
byte low,hi;


void loop() {

  BlinkLed(10);

  int serInByte=Serial.read();
  if (serInByte>0) DumpEEprom();

  ReadBmp(100);

  //SerPrintTime();
  //Serial.println();
  delay(10);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
  digitalWrite(led, HIGH);

  setTime(15,30,0,31,05,2019);

  // ---------- BMP ------------------
  Serial.println("Init BMP180 ...");
  bool success = bmp180.begin();
  if (success) {
    Serial.println("BMP180 init success");
  }
  else {
    Serial.println("BMP180 init failure !");
  }


  //---------- EEPROM ---------------
  low = EEPROM.read(0);
  hi = EEPROM.read(1);
  eepromAdr = low +hi*256;
  Serial.print("EEpromAdr:"  );
  Serial.println(eepromAdr);

}

void ReadBmp(int maxCounter)
{

  bmpReadCounter=bmpReadCounter+1;
  if (bmpReadCounter<maxCounter) return;
  bmpReadCounter=0;
  
  char status;
  double T, P, seaLevelPressure;
  bool success = false;
  
  status = bmp180.startTemperature();

  if (status != 0) 
  {
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          seaLevelPressure = bmp180.sealevel(P, alt);
          SerPrintTime();
          Serial.print(seaLevelPressure);
          Serial.print(" ");
          Serial.print(T);
          byte preasureDiff=(byte)(seaLevelPressure-DruckNullPunkt);
          WriteEEProm(preasureDiff);
          Serial.println();
        }
      }
    }
  }
}


void SerPrintTime()
{
    Serial.print(year());
    Serial.print(".");
    Serial.print(month());
    Serial.print(".");
    Serial.print(day());
    Serial.print(" ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print(" ");
}

//----------------------------------------------- EEPROM -----------------------------------------------

//gibt EEprom vom aktuellen Adresszähler rückwärts aus (neueste Werte zuerst)
void DumpEEprom()
{
    String s=Serial.readString(); //lese restliche Serielle EIngabe, um nicht auf jedes Zeichen zu reagieren und bei jedem Zeichen zu Dumpen
  
    Serial.println();
    Serial.print("Eeprom Länge:");
    Serial.print(EEPROM.length());
    Serial.print(" Eingabe:");
    Serial.print(s);
    Serial.println("----------------------------------------------");
    
    for (int i=eepromAdr; i>1;i--) //vom aktuellen Zähler rückwärts runter zu 0
    {
      PrintValueEEprom(i);
    }
    int eepromLength=EEPROM.length();
    for (int i=eepromLength; i>eepromAdr;i--) //vom oberen Ende des Eeproms rückwärts zum Zähler
    {
      PrintValueEEprom(i);
    }
    Serial.println();
    Serial.println(" ----------------------------------------------");
    Serial.println();
}

void PrintValueEEprom(int adr)
{
      int valEEprom=EEPROM.read(adr);
      valEEprom=valEEprom+DruckNullPunkt;
      Serial.print(valEEprom);
      Serial.print(" ");
      eepromDumpNewLineCounter=eepromDumpNewLineCounter+1;
      if (eepromDumpNewLineCounter>=24)
      {
        eepromDumpNewLineCounter=0;
        Serial.println();
      }
}

void WriteEEProm(byte val)
{
    
    int rest=second() % 10;  
    if (rest!=0) return; //nur alle 10 secunden speichern
    
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

    Serial.print(" --- wrote to Eprom Value:");
    Serial.print(val);
    Serial.print(" eepromAdr:");
    Serial.print(eepromAdr);
          
}

//----------------------------------------------- LED -----------------------------------------------

void BlinkLed(int maxCounter)
{
  blinkCount = blinkCount +1;
  if (blinkCount<maxCounter) return;
  
  blinkCount=0;
  int ledValue=digitalRead(led);
  digitalWrite(led, !ledValue);
  //Serial.print("Led:");
  //Serial.println(!ledValue);
  

}
