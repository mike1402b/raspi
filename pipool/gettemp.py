#!/usr/bin/python
# -*- coding: utf-8 -*-

import re, os, rrdtool, time

# function: read and parse sensor data file
def read_sensor(path):
  value = "U"
  try:
    f = open(path, "r")
    line = f.readline()
    if re.match(r"([0-9a-f]{2} ){9}: crc=[0-9a-f]{2} YES", line):
      line = f.readline()
      m = re.match(r"([0-9a-f]{2} ){9}t=([+-]?[0-9]+)", line)
      if m:
        value = str(float(m.group(2)) / 1000.0)
    f.close()
  except (IOError), e:
    print time.strftime("%x %X"), "Error reading", path, ": ", e
  return value

# define pathes to 1-wire sensor data
pathes = (
  "/sys/bus/w1/devices/28-0316362983ff/w1_slave", # raspi direkt
  "/sys/bus/w1/devices/28-0316721a7eff/w1_slave", # pool oben 4
  "/sys/bus/w1/devices/28-0516718311ff/w1_slave", # pool unten 5 - leider kaputt, liefrt U
  "/sys/bus/w1/devices/28-0316712754ff/w1_slave", # erde tief 6
  "/sys/bus/w1/devices/28-05167120f2ff/w1_slave", # erde oben 7
  "/sys/bus/w1/devices/28-051670c1a5ff/w1_slave", # kiste  unten 1  
  "/sys/bus/w1/devices/28-0516715d67ff/w1_slave", # kiste  oben 2
  "/sys/bus/w1/devices/28-051670c1a5ff/w1_slave", # außen 3
  "/sys/bus/w1/devices/28-031671a827ff/w1_slave" #solarmatte
)

# read sensor data
with open("/home/pi/raspi/pipool/1temp.txt", "a") as myfile:
    myfile.write(time.strftime("%d.%m.%Y %H:%M:%S  "))

data = 'N'
for path in pathes:
  data += ':'
  sensorValue = read_sensor(path)
  print (sensorValue)
  try:
    sensorValueFloat = float(sensorValue)
  except:
    print ("Error converting to float")
  while sensorValueFloat>90.0:
    print "wrong value, too high:", sensorValue
    sensorValue = read_sensor(path)
  data += sensorValue
  time.sleep(1)

#only 9 sensors => have to add 1 unknown values
data+=':U'

# insert data into round-robin-database
rrdtool.update(
  "%s/temp.rrd" % (os.path.dirname(os.path.abspath(__file__))),
  data)

#rrdtool.graph( "temperaturDay.png -s 'now - 1 day' -e 'now' DEF:temp0=temperature.rrd:temp1:AVERAGE  LINE2:temp0#00FF00:Innen   DEF:temp1=temperature.rrd:temp0:AVERAGE   LINE2:temp1#0000FF:Aussen")


print(time.strftime("%d.%m.%Y %H:%M:%S"))
print data

with open("/home/pi/raspi/pipool/1temp.txt", "a") as myfile:
    myfile.write(data)
    myfile.write("\n")
    

