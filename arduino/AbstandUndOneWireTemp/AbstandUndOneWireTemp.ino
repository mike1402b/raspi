#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2 // Data wire is plugged into pin 2 on the Arduino
#define TRIGGER 9 
#define ECHO    8
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
 
void setup(void)
{
  Serial.begin(9600);
  sensors.begin(); // Start up the Dallas library
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

unsigned int distance; 
 
void loop(void)
{

  //distance
  digitalWrite(TRIGGER, LOW);
  digitalWrite(TRIGGER, HIGH);
  distance = pulseIn(ECHO, HIGH);
  Serial.print("Distance:"); 
  Serial.print(distance/58);
  
  // call sensors.requestTemperatures() to issue a global temperature request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print(" Temperature:");
  Serial.println(sensors.getTempCByIndex(0)); // 0 .. first sensor on bus
  delay(100);
}
