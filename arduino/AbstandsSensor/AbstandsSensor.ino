
//Abstandssensor schaltet Relay
//den ultraschallsensor an 5v, gnd 8 (Echo) und 9 (PWM)  hängen
//relay an +5v, gnd und 11 hängen

#define TRIGGER 9 //PWM
#define ECHO    8
#define Relay  11

unsigned int distance;
double distCm;
boolean led=HIGH; //eingeschalten

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Relay, OUTPUT);
}

void loop()
{
  
  digitalWrite(LED_BUILTIN, led);
  led=!led;

  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);
  distance = pulseIn(ECHO, HIGH);
  distCm=distance / 58;
  Serial.println("Distance:" + String(distCm));

  if (distCm<15)
    digitalWrite(Relay,HIGH);
  else
      digitalWrite(Relay,LOW);

  delay(100);

}
