#!/usr/bin/python

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM) # GPIO Nummern statt Board Nummern
 
RELAIS_1_GPIO = 17
GPIO.setup(RELAIS_1_GPIO, GPIO.OUT) # GPIO Modus zuweisen
#GPIO.output(RELAIS_1_GPIO, GPIO.LOW) # aus
GPIO.output(RELAIS_1_GPIO, GPIO.HIGH) # an