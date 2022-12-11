int mode = 0;
int ledWhite = 14;
int ledYellow = 15;
int ledBlue = 16;
int ledGreen = 17;
int ledRed = 18;
int switchButton = 19;
int value = 1;
int delayVal = 1000;

void setup() {
  pinMode(ledWhite, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int voltage = analogRead(A5);

  if (voltage > 1000) {
    if (mode = 0) {
      mode = 1;
    } else if (mode == 1) {
      mode = 2;
    } else if (mode == 2) {
      mode = 3;
    } else if (mode == 3) {
      mode = 4;
    }
  }

  switch (mode) {
    case 0:
      chainForward();
      break;
    case 1:
      break;
    default:
      break;
  }

}

void chainForward() {
  showBlue();
  showYellow();
  showWhite();
  showGreen();
  showRed();



}

void showRed() {
  Serial.println("Red");
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);
  delay(delayVal);
}

void showGreen() {
  Serial.println("Green");
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  delay(delayVal);
}

void showWhite() {
  Serial.println("White");
  digitalWrite(ledWhite, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  delay(delayVal);
}

void showYellow() {
  Serial.println("Yellow");
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  delay(delayVal);
}

void showBlue() {
  Serial.println("Blue");
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  delay(delayVal);
}
