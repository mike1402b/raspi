#!/usr/bin/python

import re, os, serial, time, rrdtool

print("try open serial")
 
s = serial.Serial('/dev/ttyUSB0', 9600) # Namen ggf. anpassen
s.isOpen()

print("wait 1sec")
time.sleep(1) # der Arduino resettet nach einer Seriellen Verbindung, daher muss kurz gewartet werden
 
buf =""
data=""
print("read")

while data=="":
  	response = s.readline()
	#print(response)
  	buf = buf +response
  	#print buf
	start=buf.find('>')
	if 0<start:
		ende=buf.find('<')
		if 0<ende:
			buf = buf[start+1:ende]
			data = buf
			print("------- found:" + buf)

print "closing serial"	
s.close()
chanel=data[0:2]
analog=data[3:]
volt=float(analog)*0.0495
print "chanel:"+chanel+" analog:"+analog+" volt:"+"%.2f" % volt
dbData="N:"+"%.2f" %volt+":U:U:U:U:U:U:U"

print("writing to db:"+dbData)

rddFile="%s/solar.rrd" % (os.path.dirname(os.path.abspath(__file__)))

print("rddstr:"+rddFile)

rrdtool.update(rddFile,dbData)
