#!/usr/bin/python

import urllib

print "get AdressSearchServcie"
url = "https://todo.ab1.biz/AlCrm1708/AddressSearchService.svc"
page = urllib.urlopen(url).read()
print page;
print "------------------------------------------"

page = urllib.urlopen("http://t7.azurewebsites.net/TL/TLV").read()
print page;
print "------------------------------------------"

page = urllib.urlopen("http://t3.azurewebsites.net/TL/TLV").read()
print page;
print "------------------------------------------"
