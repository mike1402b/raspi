
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int count =0;
bool ledHigh=true;

// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(led, OUTPUT);  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  double volt=sensorValue*0.0495; //ca 50/1023
  // print out the value you read:
  Serial.print(">A0:");
  Serial.print(sensorValue);
  Serial.print("< (");
  Serial.print(volt);
  Serial.print(" )");
  Serial.println();
  delay(1);        // delay in between reads for stability
  count = count +1;
  if (count>200)
  {
    count=0;
    if (ledHigh)
    {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    else
    {
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    }
    ledHigh = !ledHigh;
  }
}
