
// the setup function runs once when you press reset or power the board
#define TRIGGER 9 //PWM
#define ECHO    8

unsigned int distance;
boolean led=HIGH;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(2,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  
  digitalWrite(LED_BUILTIN, led);
  led=!led;
  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);
  distance = pulseIn(ECHO, HIGH);
  Serial.println("z:0 A0:" + String(distance / 58) + " A1:0");
  delay(50);

}
