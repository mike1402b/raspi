
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int r12 = 12;
int r11 = 11;
int r10 = 10;
int r09 = 9;

int count =0;
bool ledHigh=true;

int serInByte=-1;
int serBuf[3];
const byte analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 }; //A0=14 beim Uno, A1=15

// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(led, OUTPUT);  
  pinMode(r12, OUTPUT); 
  pinMode(r11, OUTPUT); 
  pinMode(r10, OUTPUT); 
  pinMode(r09, OUTPUT); 
  SetPins(true);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Ready ! Type in");
}

// the loop routine runs over and over again forever:
void loop() 
{
  
  serInByte=Serial.read(); //reads after return
  if (0<serInByte)
  {
    ShiftBuf();
    if (10==serBuf[3])
    {
      PrintBuf(); //AscII Code der einzelnen Zeichen
      CheckBuf(); //Befehlsausführung (Analog Read oder Digital out)
      Serial.println(); //Leerzeile
    }

  }

  //delay(1); //kein delay, verursacht Probleme beim serial Read

  BlinkLed();

}

void BlinkLed()
{
  count = count +1;
  if (count>32000)
  {
    count=0;
    
    int ledValue=digitalRead(led);
    digitalWrite(led, !ledValue);
    //Serial.print("Led:");
    //Serial.println(!ledValue);
    
  }
}

void ShiftBuf()
{
    serBuf[0]=serBuf[1];
    serBuf[1]=serBuf[2];
    serBuf[2]=serBuf[3];
    serBuf[3]=serInByte;
}

void CheckBuf()
{
      byte pinNr=byte((serBuf[1]-49)*10+serBuf[2]-49);

      if (66==serBuf[0]) //A...Analog
      {
          Serial.print("Analog PinNr.: ");
          int analogPin=analogPins[pinNr];
          Serial.print(analogPin);
          Serial.print("  Value: ");
          int analogValue = analogRead(analogPin);
          Serial.print(analogValue);
          double volt=analogValue*0.0495; //ca 50/1023 5V=1023, Spannungsteiler=1:10 (100kOhm/1000kOhm)
          Serial.print(" Volt:");
          Serial.println(volt);

          /* Old AnalogRead Format (Channelnr)
          Serial.print(">A0:");
          Serial.print(analogValue);
          Serial.print("< (");
          Serial.print(volt);
          Serial.print(" ) ledHigh:");
          Serial.print(ledHigh);
          Serial.print(" count:");
          Serial.print(count);
          Serial.println();
          */
          
      }
      else if (69==serBuf[0]) //D ... Digital
      {
          Serial.print("Digital pinNr:");
          Serial.print(pinNr);
          int val=digitalRead(pinNr);
          Serial.print(" value:");
          Serial.println(val);
          digitalWrite(pinNr,!val);
          //SetPins(!val);
      }
      else
      {
          Serial.print("commands: A01...A08, D09..D12 not found:");
          Serial.println(serBuf[0]);
      }
}

void PrintBuf()
{
    Serial.print("Buffer: ");
    Serial.print(serBuf[0]);
    Serial.print(" ");
    Serial.print(serBuf[1]);
    Serial.print(" ");
    Serial.print(serBuf[2]);
    Serial.print(" ");
    Serial.println(serBuf[3]);
}

void SetPins(bool on)
{
     if (on)
    {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(r12, HIGH);   
      digitalWrite(r11, HIGH);   
      digitalWrite(r10, HIGH);   
      digitalWrite(r09, HIGH);   
      Serial.println("switched high");
    }
    else
    {
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(r12, LOW);   
      digitalWrite(r11, LOW);   
      digitalWrite(r10, LOW);   
      digitalWrite(r09, LOW);   
      Serial.println("switched to low");
    }
 
}
  
