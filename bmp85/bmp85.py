#!/usr/bin/python

import re, os, rrdtool, time
from Adafruit_BMP085 import BMP085


# ===========================================================================
# Example Code
# ===========================================================================

# Initialise the BMP085 and use STANDARD mode (default value)
# bmp = BMP085(0x77, debug=True)
bmp = BMP085(0x77)

# To specify a different operating mode, uncomment one of the following:
# bmp = BMP085(0x77, 0)  # ULTRALOWPOWER Mode
# bmp = BMP085(0x77, 1)  # STANDARD Mode
# bmp = BMP085(0x77, 2)  # HIRES Mode
# bmp = BMP085(0x77, 3)  # ULTRAHIRES Mode

temp = bmp.readTemperature()

# Read the current barometric pressure level
pressure = bmp.readPressure()

# To calculate altitude based on an estimated mean sea level pressure
# (1013.25 hPa) call the function as follows, but this won't be very accurate
altitude = bmp.readAltitude()

# To specify a more accurate altitude, enter the correct mean sea level
# pressure level.  For example, if the current pressure level is 1023.50 hPa
# enter 102350 since we include two decimal places in the integer value
# altitude = bmp.readAltitude(102350)

pressureHPa=pressure / 100.0

print "Temperature: %.2f C" % temp
print "Pressure:    %.2f hPa" % pressureHPa
print "Altitude:    %.2f" % altitude

data = 'N:'+str(temp)+":"+str(pressureHPa)+":"+str(altitude)
print "adding to rrd database: "+data

# insert data into round-robin-database (__file__ ist das aktuelle file (dieses script))
#rddtool.update(file,stringDaten)
rrdtool.update(
  "%s/bmp.rrd" % (os.path.dirname(os.path.abspath(__file__))),
  data)
