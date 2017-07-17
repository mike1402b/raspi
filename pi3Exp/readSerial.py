#!/usr/bin/python

import serial
import time

print("try open serial")
 
s = serial.Serial('/dev/ttyUSB0', 9600) # Namen ggf. anpassen
s.isOpen()

print("wait 1sec")
time.sleep(1) # der Arduino resettet nach einer Seriellen Verbindung, daher muss kurz gewartet werden
 
buf =""
print("read")

try:
    while True:
        response = s.readline()
        #print(response)
	buf = buf +response
	#print buf
	start=buf.find('>')
	if 0<start:
		ende=buf.find('<')
		if 0<ende:
			buf = buf[start+1:ende]
			print("------- found:" + buf)
	
except KeyboardInterrupt:
    s.close()

