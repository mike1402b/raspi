/*
Richtungsumkehr
schaltet 3 Relays:
Hauptschalter einAus
Umschalter u1 und u2, die die Stromrichtung umkehren (während der Umkehr ist der Hauptschalter ausgeschaltet)
*/

const long umschaltdauer=30*1000; //sekunden*1000=ms
const int u1=4; //Richtungs Umschalt relay 1
const int u2=6; //Richtungs Umschalt relay 2
const int einAus=5; //Hauptschalter relay
const int In4=7; //freies Relay


void SetOutput()
{
  pinMode(In4, OUTPUT);
  pinMode(einAus, OUTPUT);
  pinMode(u1, OUTPUT);
  pinMode(u2, OUTPUT);
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Setup Begin");
  SetOutput();
  Init(HIGH);
  Serial.println("Setup End");
}

void Init(int Val) //High=Relay aus
{
  Serial.println("Init Begin");
  digitalWrite(In4, Val);
  digitalWrite(einAus, Val);
  digitalWrite(u2, Val);  
  digitalWrite(u1, Val);  
  Serial.println("Init End");
}

void Umschalten(int Richtung)
{
  digitalWrite(u1, Richtung);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(u2, Richtung);  // turn the LED on (HIGH is the voltage level)
}

void Ausschalten()
{
    digitalWrite(einAus, HIGH);
    delay(1000); //warte damit Freilaufstrom Magnetfeld abgebaut hat
}

void Einschalten()
{
    digitalWrite(einAus, LOW);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("loop Begin - Richtung 1");

  Ausschalten();
  Umschalten(HIGH);
  Einschalten();
  delay(umschaltdauer);                      // wait for a second

  Serial.println("andere Richtung 2");
  Ausschalten();
  Umschalten(LOW);
  Einschalten();
  delay(umschaltdauer);                      // wait for a second
}
