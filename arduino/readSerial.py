#!/usr/bin/python

import serial
import time

print("try open serial")
 
s = serial.Serial('/dev/ttyUSB0', 9600) # Namen ggf. anpassen
s.isOpen()

print("wait 2sec")
time.sleep(2) # der Arduino resettet nach einer Seriellen Verbindung, daher muss kurz gewartet werden
 
print("read")

try:
    while True:
        response = s.readline()
        print(response)
except KeyboardInterrupt:
    s.close()

