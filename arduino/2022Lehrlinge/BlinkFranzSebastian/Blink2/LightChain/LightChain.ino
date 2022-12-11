int lightChain = 10;


void setup() {
  pinMode(lightChain, OUTPUT);
}

void loop() {
  digitalWrite(lightChain, HIGH);
  delay(2000);
  digitalWrite(lightChain, LOW);
  delay(2000);
}
