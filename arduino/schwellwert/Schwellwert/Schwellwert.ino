
int s1=900; //bei Überschreiten ein
int s2=600; //bei UNterschreiten wieder aus
int ledPin=8;
bool led=LOW;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("------------------------ Schwellwert Beginn ------------------------------");
  pinMode(ledPin, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("Value=");
  Serial.println(sensorValue);

  if (sensorValue>s1)
  {
    digitalWrite(ledPin,HIGH);
  }
  
  if (sensorValue<s2)
  {
    digitalWrite(ledPin,LOW);
  }
  

  delay(1);        // delay in between reads for stability
}
