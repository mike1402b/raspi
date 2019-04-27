#!/usr/bin/python

import urllib

print "get AdressSearchServcie"
url = "http://192.168.1.13"
page = urllib.urlopen(url).read()
print page;
print "------------------------------------------"

#page = urllib.urlopen("http://192.168.1.12/wizard/public/").read()
#print page;
print "------------------------------------------"

#page = urllib.urlopen("http://t3.azurewebsites.net/TL/TLV").read()
#print page;
#yprint "------------------------------------------"
