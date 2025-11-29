/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    digitalWrite(2, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second

    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    digitalWrite(2, LOW);   // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a second
    delay(1);  // delay in between reads for stability
}
