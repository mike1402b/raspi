/*
  WASSERMELDER
  Wenn A0 0 wird (genügt wenn A0 über  Wasser mit  GND  verbunden  wird)  werden  die  Pins  4 und 5 eingeschaltet, für Relay und LED
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4,OUTPUT);  
  pinMode(5,OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  if (sensorValue==0)
  {
    digitalWrite(LED_BUILTIN, HIGH); 
    digitalWrite(4, HIGH); 
    digitalWrite(5, HIGH); 
  }
  else
  {
     digitalWrite(LED_BUILTIN, LOW); 
     digitalWrite(4, LOW); 
     digitalWrite(5, LOW); 
  }
  delay(1);        // delay in between reads for stability
}
