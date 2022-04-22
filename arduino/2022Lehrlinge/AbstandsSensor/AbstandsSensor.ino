
// the setup function runs once when you press reset or power the board
#define TRIGGER 9 
#define ECHO    8

unsigned int distance;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(2,OUTPUT);
}

void loop()
{
  digitalWrite(2, LOW);
  delay(250);
  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);
  distance = pulseIn(ECHO, HIGH);
  Serial.println("z:0 A0:" + String(distance / 58) + " A1:0");
  digitalWrite(2, HIGH);
  
  delay(250);

}
