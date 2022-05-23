#define pirSensorPin 7
#define Activebuzzer 11
#define relay 12

// Globale Variablen
int statusPirSensor = 0;
bool motionState = false;// init. Bewegungsstatus

//setup: Arduino und Umgebung initialisieren
void setup() {
  // Setup I/O STatus für Pins
  pinMode(Activebuzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(pirSensorPin, INPUT);
}

//loop Funktion: Komplette Logik für den Microcontroller
void loop() {
  // Wir lesen den pirSensorPin ein
  statusPirSensor = digitalRead(pirSensorPin);

  if (statusPirSensor == HIGH) {
    // Bewegung erkannt
    tone(Activebuzzer, 440, 800);//Ausgabe Ton A für 800 ms
    digitalWrite(relay,HIGH);
    // Update Variable motionState
    if (motionState == false) {
      motionState = true;
    }
  }
  // Keine Bewegung erkannt (pirSensorPin = LOW)
  else {
    noTone(Activebuzzer);//Eigentlich nicht notwendig
    digitalWrite(relay,LOW);
    if (motionState == true) {
      motionState = false;
    }
  }
  delay(10);//extra Verzögerung für die loop-Funktion
}
