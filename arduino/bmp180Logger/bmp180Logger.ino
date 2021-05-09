#include <EEPROM.h>
#include <Wire.h>
#include <TimeLib.h>
#include <SFE_BMP180.h>

/*
 * LUFTDRUCK MESSUNG mit speicherung im EPROM (Arduino 1024 Bytes)
 * HHmmssddMMyyyy z.b. 21553001072019
 * niedrigster Luftdruck: 870 hPa (12.10.1979 im Taifun Tip, Guam Nordwestpazifik), stärkster Abfall: in 24h 98hPa 2005 Hurrikan Wilma, 882hPa
 * höchster Luftdruck: 1084hPa in Mongolei, 1060 hPa 1907 in Greifswald Deutschland)
 * => nehme 850 als 0 Punkt und speichere differenz dazu in bytes im EEprom, die letzten 4 (251-254) als Steuercodes, 255 ist meist initialwert, eventuel auch 0 ?
 * 254 = Programmstart, anschließend 4 Bytes Jahr Monat Tag Stunde, dann stündlich ein Wert => komme ca 42 Tage aus
 * EEProm (0)=Low Byte aktueller Zähler
 * EEProm (1)=High Byte aktueller Zähler
 * bei Programmstart erhöhe Zähler um 1 und schreibe aktuelles Datum und Uhrzeit rein (von Serieller lesen)
  
 */

bool debug=false;
int led = 13; // Pin 13 has an LED connected on most Arduino boards.
int blinkCount=0;

//---Printing
int lastsecond=-1;
int lastminute=-1;


//-----BMP------------
SFE_BMP180 bmp180;
float alt = 400; // Altitude of current location in meters
int DruckNullPunkt=850;
int bmpReadCounter=0; //alle x Schleifendurchläufe lesen
double T, P, seaLevelPressure;
byte preasureDiff=0;


//----------- EEprom ----------
/*
 * 0 low
 * 1 high
 * 2 sec
 * 3 min
 * 4 stunde
 * 5 tag
 * 6 monat
 * 7 jahr
 * 
 */

int eepromAdr=8; // die ersten 2 Bytes sind für den Adresszähler reserviert, vor erstem Schreiben wird der Zähler erhöht
int eePromAdrMin=8;
int eepromDumpNewLineCounter=0; //EEprom NewLineCounter
byte low,hi;
int eepromLastMinute=-1; // Minute, wann das Eeprom zuletzt geschrieben wurde
int eepromEveryMinute=30; //wieviel Minuten Abstand



// ---------------------- loop ------------
void loop() {

  BlinkLed(10);



  int serCount=Serial.available();
  if (serCount>0) SerCommand(serCount);

  ReadBmp(100);

  PrintEverySecond();
  
  delay(10);
}

// ---------------------- Setup -------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
  digitalWrite(led, HIGH);

  setTime(15,29,0,31,05,2019);

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
  if (eepromAdr<eePromAdrMin)
  {
    eepromAdr=eePromAdrMin;
  }
  Serial.print("EEpromAdr:"  );
  Serial.println(eepromAdr);

  int se = EEPROM.read(2);
  int mi = EEPROM.read(3);
  int hr = EEPROM.read(4);
  int dd = EEPROM.read(5);
  int mo = EEPROM.read(6);
  int yy = EEPROM.read(7);

  setTime(hr, mi, se, dd, mo, yy);
  
  eepromLastMinute=minute();

}

void SerCommand(int byteCount)
{
  Serial.println();
  Serial.print("-------------- Serielle Eingabe Länge:");
  Serial.print(byteCount);
  Serial.println();
  
  if (byteCount>6) 
    SetTime();
  else
    DumpEEprom();

  Serial.readString(); //lese eventuelle überreste
}

void PrintEverySecond()
{
  if (second()!=lastsecond) // every Second
  {
    lastsecond=second();
    EEPROM.write(2, second());

    PrintEveryMinute();
  
    if (second() % 2 == 0)
    {
      Serial.print(" ");
      Serial.print(seaLevelPressure,0);
    }
    else 
    {
      Serial.print(" ");
      Serial.print(T,0);
    }
  }
}

void PrintEveryMinute()
{

  
  if (minute()!=lastminute) 
  {
    
    lastminute=minute();
    WriteTimeToEprom();
    WriteEEProm(preasureDiff);
    
    Serial.println();
    SerPrintTime();
  }
}

void WriteTimeToEprom()
{
    EEPROM.write(2, second()); 
    EEPROM.write(3, minute());
    EEPROM.write(4, hour());
    EEPROM.write(5, day());
    EEPROM.write(6, month());
    EEPROM.write(7, year());
}

void SetTime()
{
      int i = 0;
    char incoming[15] = {}; //wegen Endzeichen
    
    //Array of Char leeren
    memset(incoming, 0, sizeof(incoming));
    //Zeit wird geliefert als HHmmssddMMyyyy, z.B. 23120027112012
    while (Serial.available() > 0 && i < sizeof(incoming) - 1) {
      incoming[i] = Serial.read();
      i++;
      delay(3);
    }

    Serial.readString(); //lese eventuelle überreste
     
    //in Zeit umwandeln
    char hr[3] = {};
    char min[3] = {};
    char sec[3] = {};
    char day[3] = {};
    char month[3] = {};
    char yr[5] = {};
    hr[0] = incoming[0];
    hr[1] = incoming[1];
    min[0] = incoming[2];
    min[1] = incoming[3];
    sec[0] = incoming[4];
    sec[1] = incoming[5];
    day[0] = incoming[6];
    day[1] = incoming[7];
    month[0] = incoming[8];
    month[1] = incoming[9];
    yr[0] = incoming[10];
    yr[1] = incoming[11];
    yr[2] = incoming[12];
    yr[3] = incoming[13];
    
    setTime(atoi(hr), atoi(min), atoi(sec), 
      atoi(day), atoi(month), atoi(yr));
    

    Serial.print("------------------------- new Time set:");
    SerPrintTime();
    Serial.println();

    WriteTimeToEprom();
}



void ReadBmp(int maxCounter)
{

  /*
  bmpReadCounter=bmpReadCounter+1;
  if (bmpReadCounter<maxCounter) return;
  bmpReadCounter=0;
*/
  
  char status;
  
  bool success = false;
  
  status = bmp180.startTemperature();

  if (status != 0) 
  {
    delay(200); //Delay, sonst falsche Luftdruck messwerte
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          seaLevelPressure = bmp180.sealevel(P, alt);
          /*
          Serial.print(" ");
          Serial.print(seaLevelPressure,0);
          Serial.print(" ");
          Serial.print(T,0);
          */
         
          preasureDiff=(byte)(seaLevelPressure-DruckNullPunkt);

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
  /*
    if (0!=second()) return; //nur zur vollen Minute
    int rest=minute() % 5;  //nur alle x min Speichern
    if (rest!=0) return; 
    */
    int diff=abs(minute()-eepromLastMinute);
    if (diff<eepromEveryMinute) return;
    eepromLastMinute=minute();
    
    eepromAdr=eepromAdr+1; //niemals drüberschreiben
    EEPROM.write(eepromAdr, val);
    if (eepromAdr == EEPROM.length()) 
    {
      eepromAdr = eePromAdrMin; //ersten 2 Bytes für den Adresszähler, wird ja erhöt vor dem 1. Mal schreiben
    }
    low = lowByte(eepromAdr);
    hi = highByte(eepromAdr);
    EEPROM.write(0, low);
    EEPROM.write(1, hi);

    Serial.println();
    Serial.print(" --- wrote to Eprom Value:");
    Serial.print(val);
    Serial.print(" eepromAdr:");
    Serial.print(eepromAdr);
    Serial.println();
          
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
