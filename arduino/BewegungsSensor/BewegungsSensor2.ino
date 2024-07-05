#define pirSensorPin 7
#define Activebuzzer 11
#define interneLed 13

// Globale Variablen
int statusPirSensor = 0;
bool motionState = false;// init. Bewegungsstatus

//setup: Arduino und Umgebung initialisieren
void setup() {
  // Setup I/O STatus für Pins
  pinMode(Activebuzzer, OUTPUT);
  pinMode(pirSensorPin, INPUT);
   Serial.begin(9600);
}

//loop Funktion: Komplette Logik für den Microcontroller
void loop() {
  // Wir lesen den pirSensorPin ein
  statusPirSensor = digitalRead(pirSensorPin);

  if (statusPirSensor == HIGH) {
    digitalWrite(interneLed, HIGH);
    tone(Activebuzzer, 440, 800);//Ausgabe Ton A für 800 ms
    // Update Variable motionState
    if (motionState == false) {
      Serial.println("Bewegung erkannt");  
      motionState = true;
    }
  }
  // Keine Bewegung erkannt (pirSensorPin = LOW)
  else {
    digitalWrite(interneLed, LOW);
    noTone(Activebuzzer);//Eigentlich nicht notwendig
    if (motionState == true) {
      Serial.println("keine Bewegung");
      motionState = false;
    }
  }
  delay(10);//extra Verzögerung für die loop-Funktion
}
