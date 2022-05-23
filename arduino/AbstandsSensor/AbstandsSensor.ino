
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
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  
  digitalWrite(LED_BUILTIN, led);
  led=!led;
  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);
  distance = pulseIn(ECHO, HIGH);
  Serial.println("Distance:" + String(distance / 58));
  delay(50);

}
