#define PIN_IN1 8  // blue
#define PIN_IN2 9  // pink
#define PIN_IN3 10 // yellow
#define PIN_IN4 11 // orange

//Abstandssensor
#define TRIGGER 7 //PWM
#define ECHO    6

long distance;
long echotime;

unsigned int lowSpeed  = 2000; // max: 16000, delay in ms
unsigned int highSpeed =  800;

void setup()
{
   Serial.begin(9600);
   Serial.println("Setup");
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_IN3, OUTPUT);
    pinMode(PIN_IN4, OUTPUT);
}

void loop()
{

  
    unsigned long n = millis() / 500; // 0,5 second

    switch(n % 10) {
        case 0: rotateRight(highSpeed); break;
        case 1: rotateRight(highSpeed); break;
        case 2: rotateRight(highSpeed); break;
        case 3: rotateRight(highSpeed); break;
        case 4: rotateRight(highSpeed); break;
        case 5: rotateLeft(highSpeed);  break;
        case 6: rotateLeft(highSpeed);  break;
        case 7: rotateLeft(highSpeed);  break;
        case 8: rotateLeft(highSpeed);  break;
        case 9: rotateLeft(highSpeed);  break;
        
    }
}

void rotateRight(unsigned int motorSpeed)
{
    Serial.println("rotateRight");
    setMotor(LOW, LOW, LOW, HIGH, motorSpeed);
    setMotor(LOW, LOW, HIGH, HIGH, motorSpeed);
    setMotor(LOW, LOW, HIGH, LOW, motorSpeed);
    setMotor(LOW, HIGH, HIGH, LOW, motorSpeed);
    setMotor(LOW, HIGH, LOW, LOW, motorSpeed);
    setMotor(HIGH, HIGH, LOW, LOW, motorSpeed);
    setMotor(HIGH, LOW, LOW, LOW, motorSpeed);
    setMotor(HIGH, LOW, LOW, HIGH, motorSpeed);
}

void rotateLeft(unsigned int motorSpeed)
{
    Serial.println("rotateLeft");  
    setMotor(HIGH, LOW, LOW, LOW, motorSpeed);
    setMotor(HIGH, HIGH, LOW, LOW, motorSpeed);
    setMotor(LOW, HIGH, LOW, LOW, motorSpeed);
    setMotor(LOW, HIGH, HIGH, LOW, motorSpeed);
    setMotor(LOW, LOW, HIGH, LOW, motorSpeed);
    setMotor(LOW, LOW, HIGH, HIGH, motorSpeed);
    setMotor(LOW, LOW, LOW, HIGH, motorSpeed);
    setMotor(HIGH, LOW, LOW, HIGH, motorSpeed);
}

void stopMotor()
{

  
    Serial.println("Stop");  
    setMotor(LOW, LOW, LOW, LOW, 0);
}

void setMotor(byte in1, byte in2, byte in3, byte in4, unsigned int motorSpeed)
{
      
    digitalWrite(PIN_IN1, in1);
    digitalWrite(PIN_IN2, in2);
    digitalWrite(PIN_IN3, in3);
    digitalWrite(PIN_IN4, in4);
    delayMicroseconds(motorSpeed);
}
