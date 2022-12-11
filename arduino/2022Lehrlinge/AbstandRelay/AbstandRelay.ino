
// the setup function runs once when you press reset or power the board
#define TRIGGER 8 
#define ECHO    9

unsigned int distance;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(2,OUTPUT);
  pinMode(7, OUTPUT);// connected to S terminal of Relay
}

void loop()
{
  digitalWrite(2, LOW);
  delay(250);
  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);

  distance = pulseIn(ECHO, HIGH);
  Serial.println("z:0 A0:" + String(distance / 58) + " A1:0");
  if(distance != 0){
  if(distance/58 < 30 && distance != 0){
        digitalWrite(7,HIGH);// turn relay ON´
  }else{
        digitalWrite(7, LOW);// turn relay OFF
  }
  }
  
  digitalWrite(2, HIGH);
  delay(250);


}
