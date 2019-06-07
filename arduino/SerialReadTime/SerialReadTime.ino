#include <TimeLib.h>


char incoming[15] = {}; //wegen Endzeichen
int led = 13; 
int lastSecond=-1; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int i = 0;

   if (Serial.available() > 10) 
   {
    //Array of Char leeren
    memset(incoming, 0, sizeof(incoming));
    //Zeit wird geliefert als HHmmssddMMyyyy, z.B. 23120027112012
    while (Serial.available() > 0 && i < sizeof(incoming) - 1) {
      incoming[i] = Serial.read();
      i++;
      delay(3);
    }
     
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
    Serial.println("!new Time set");
    Serial.readString(); //lese eventuelle überreste
  }
 

  
  SerPrintTime();
  delay(1000);
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
    Serial.println();
}
