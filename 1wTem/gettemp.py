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
  "/sys/bus/w1/devices/28-0316368011ff/w1_slave",
  "/sys/bus/w1/devices/28-03163690c5ff/w1_slave"
)

# read sensor data
with open("1temperatur.txt", "a") as myfile:
    myfile.write(time.strftime("%d.%m.%Y %H:%M:%S  "))

data = 'N'
for path in pathes:
  data += ':'
  sensorValue = read_sensor(path)
  sensorValueFloat = float(sensorValue)
  while sensorValueFloat>60.0:
    print "wrong value, too high:", sensorValue
    sensorValue = read_sensor(path)
  data += sensorValue
  time.sleep(1)

# insert data into round-robin-database (__file__ ist das aktuelle file (dieses script))
#rddtool.update(file,stringDaten)
rrdtool.update(
  "%s/temperature.rrd" % (os.path.dirname(os.path.abspath(__file__))),
  data)

#rrdtool.graph( "temperaturDay.png -s 'now - 1 day' -e 'now' DEF:temp0=temperature.rrd:temp1:AVERAGE  LINE2:temp0#00FF00:Innen   DEF:temp1=temperature.rrd:temp0:AVERAGE   LINE2:temp1#0000FF:Aussen")


print(time.strftime("%d.%m.%Y %H:%M:%S"))
print data

with open("1temperatur.txt", "a") as myfile:
    myfile.write(data)
    myfile.write("\n")
    

