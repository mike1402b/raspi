#include <Arduino.h>

//TODO: Stunden funktionieren nicht wirklich
 
int ledPin=8; //schaltPin

struct Zeit {
  int h;
  int m;
  int s;
};

//---------------------------------- ANPASSEN VOR PROGRAMMSTART -------------------------------------------
Zeit startZeit = { 8 , 59, 58};
Zeit schaltZeiten[]  = { {9,0,0}, {10,0,0}, {11,0,0}, {13,0,0} };
//---------------------------------------------------------------------------------------------------------

int schaltZeitenAnz = sizeof(schaltZeiten) / sizeof(schaltZeiten[0]);
Zeit sinceStart;
Zeit now;
   
void setup() {

  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("---------- Zeitschaltuhr Setup: Startzeit=");
  ZeitPrint(startZeit);
  Serial.println("------------");
  
  pinMode(ledPin, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
}

bool sw=LOW;
 
void loop() {

  unsigned long secSinceStart = millis()/ 1000; 
  
  sinceStart.h = secSinceStart / 3600;
  sinceStart.m = (secSinceStart % 3600) / 60;
  sinceStart.s = secSinceStart % 60;

  now=ZeitAdd(startZeit,sinceStart);
  
  //Serial.print("sinceStart=");
  //ZeitPrint(sinceStart);
  Serial.print(" now=");
  ZeitPrint(now);


  sw=LOW;
  for (int i=0;i<schaltZeitenAnz;i++)
  {
    Serial.print(" sz(");
    Serial.print(i);
    Serial.print(")=");
    ZeitPrint(schaltZeiten[i]);

    if (Zeit2Groesser(schaltZeiten[i],now)) //wenn die aktuelle Zeit groesser als die Schaltzeit ist, wird geschalten
    {
      Serial.print("x");
      sw=!sw;  
    }
    else
    {
      Serial.print("_");
    }
    Serial.print(sw);
    Serial.print(" ");
  }
  digitalWrite(ledPin, sw);
  Serial.println();

  BlinkInternalLed();
}

void BlinkInternalLed()
{
  //blink internal led to show alive  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}


bool Zeit2Groesser(Zeit z1,Zeit z2)
{
  long s1=z1.h*60*60+z1.m*60+z1.s;
  long s2=z2.h*60*60+z2.m*60+z2.s;
  return s2>s1;
}

Zeit ZeitAdd2(Zeit z1, Zeit z2)
{
  Zeit z={0,0,0};
  return z;
}

Zeit ZeitAdd(Zeit z1, Zeit z2)
{
  Zeit z={0,0,0};
  z.s=z1.s+z2.s;
  if (z.s>59)
  {
    z.s=z.s-60;
    z.m=1;
  }
  z.m=z.m+z1.m+z2.m;
  if (z.m>59)
  {
    z.m=z.m-60;
    z.h=1;
  }
  z.h=z.h+z1.h+z2.h;
  while (z.h>24)
  {
    z.h=z.h-24;
  }
  return z;
}


void ZeitPrint(Zeit z)
{
  Serial.print((z.h < 10 ? "0" : "") + String(z.h) + ":");
  Serial.print((z.m < 10 ? "0" : "") + String(z.m) + ":");
  Serial.print((z.s  < 10 ? "0" : "") + String(z.s ));
}

 
