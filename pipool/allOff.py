#!/usr/bin/python

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM) # GPIO Nummern statt Board Nummern
 
R1 = 23
R2 = 24
R3 = 25
R4 = 16
GPIO.setup(R1, GPIO.OUT) # GPIO Modus zuweisen
GPIO.output(R1, GPIO.HIGH) # aus

GPIO.setup(R2, GPIO.OUT) # GPIO Modus zuweisen
GPIO.output(R2, GPIO.HIGH) # aus

GPIO.setup(R3, GPIO.OUT) # GPIO Modus zuweisen
GPIO.output(R3, GPIO.HIGH) # aus

GPIO.setup(R4, GPIO.OUT) # GPIO Modus zuweisen
GPIO.output(R4, GPIO.HIGH) # aus
