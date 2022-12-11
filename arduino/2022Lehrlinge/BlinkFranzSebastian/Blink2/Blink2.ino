int mode = 0;
int ledRed = 7;
int ledBlue = 4;
int switchButton = 19;
int value = 1;
bool flag;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println(flag);
  int voltage = analogRead(A5);

  if (voltage > 1000) {
    if (flag == true) {
      flag = false;
    } else {
      flag = true;
    }
  }

  if (flag == true) {
    lightylightlightfast();
  }

  if (flag == false) {
    lightylightlightslow();
  }
}

void lightylightlightfast() {
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledRed, LOW);
  delay(250);
  digitalWrite(ledRed , HIGH);
  digitalWrite(ledBlue, LOW);
  delay(250);
}

void lightylightlightslow() {
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledRed, LOW);
  delay(1000);
  digitalWrite(ledRed , HIGH);
  digitalWrite(ledBlue, LOW);
  delay(1000);
}
