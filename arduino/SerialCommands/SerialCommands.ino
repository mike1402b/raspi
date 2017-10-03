// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int count =0;
bool ledHigh=true;

char buffer[100];
byte pos=0;

void setup() 
{
  pinMode(led, OUTPUT);  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {
  
  /*
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  double volt=sensorValue*0.0495; //ca 50/1023
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print(" : ");
  Serial.println(volt);
  */
  byte in = Serial.read();
  if (in<255)
  {
    
//    Serial.print("got: ");
 //   Serial.print(in);
    char c=in;
    Serial.print(c);
    buffer[pos]=c;
    pos=pos+1;
    if (pos>1)
    {
      pos=0;
      DoCommand();

    }
  }
  
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
    delay(1);        // delay in between reads for stability
}

void DoCommand()
{
      Serial.println();
      Serial.print("buffer:");
      Serial.print(buffer[0]);
      Serial.print(buffer[1]);
      
      switch (buffer[0])
      {
        case 'A':
          Serial.print(" => Analog Read: ");
          AnalogRead();
          break;
        case 'D':
          Serial.print(" => Digital Out:");
          break;
        default:
          Serial.print(" => noch nicht implementiert:");
      }
      Serial.println();
}

void AnalogRead()
{
    int sensorValue = analogRead(A0);
  double volt=sensorValue*0.0495; //ca 50/1023
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print(" : ");
  Serial.print(volt);
}
