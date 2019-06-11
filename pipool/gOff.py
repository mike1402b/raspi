#!/usr/bin/python
import sys
print "This is the name of the script: ", sys.argv[0]
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM) # GPIO Nummern statt Board Nummern
 
RELAIS_1_GPIO = int(sys.argv[1])
GPIO.setup(RELAIS_1_GPIO, GPIO.OUT) # GPIO Modus zuweisen
GPIO.output(RELAIS_1_GPIO, GPIO.LOW) # aus
#GPIO.output(RELAIS_1_GPIO, GPIO.HIGH) # an
