
int s1=585; // 585=12,8V bei Überschreiten ein
int s2=575; // 575=12,6V bei UNterschreiten wieder aus
int ledPin=11; //nano D11  uno z.b. 8


//--------------- Widerstände für Spannungsteiler zum Begrenzen
double R2=10; //10 MOhm braun schwarz blau
double R1=33; //33 MOhm orange orange blau
double calcTeiler=(R1+R2)/R2; // am  kleinere R2 wird der Spannungsabfall gemessen

double calc5=5.0/1024.0;

bool led=LOW;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println();
  Serial.println("------------------------ Schwellwert Beginn ------------------------------");
  Serial.print("Analog In=A7, SchaltPin=");
  Serial.println(ledPin);
  Serial.println("--------------------------------------------------------------------------");
  pinMode(ledPin, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {

  int sensorValue = analogRead(A7);
  Serial.print("S=");
  Serial.print(sensorValue);
  
  double volt5=sensorValue;
  volt5=volt5*calc5;
  Serial.print(" V5=");
  Serial.print(volt5);

  double voltTeiler=volt5*calcTeiler;
  Serial.print(" VTeiler=");
  Serial.print(voltTeiler);

  Serial.print(" R1=");
  Serial.print(R1,0); //0 nachkommastellen
  Serial.print(" R2=");
  Serial.print(R2,0);

  
  Serial.println();

  if (sensorValue>s1)
  {
    digitalWrite(ledPin,HIGH);
  }
  
  if (sensorValue<s2)
  {
    digitalWrite(ledPin,LOW);
  }
  

  delay(300);        // delay in between reads for stability
}
