1) git clone ...
2) ./install.sh #installiert notwendige software
3a) i2c initialisieren
sudo nano /etc/modules
An das Ende der Datei werden diese beiden Zeilen hinzugefügt:
i2c-bcm2708
i2c-dev

sudo nano /etc/modprobe.d/raspi-blacklist.conf
#blacklist spi-bcm2708
#blacklist i2c-bcm2708

sudo raspi-config
interface options i2c aktivieren
sudo reboot

3b) i2cdetect -y 1 #sollte unter 77 etwas anzeigen:
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- 77

4) ./createRrd.sh #erzeugt rrd datenbank - nur wenn noch nciht vorhanden
5) ./bmp85.py auslesen temperatur testen (rrdtool update wird fehler mverursachen, wenn noch keine db da)
6) crontab -e 
*/5  * * * * $HOME/raspi/bmp85/bmp85.py > $HOME/log/bmp85.log 2>&1
*/15 * * * * $HOME/raspi/pipool/tGraph.sh > $HOME/log/tGraph.log 2>&1
*/10 * * * * $HOME/raspi/allgemein/htmlGetSites.py

7) ./wwwInit.sh #kopiert index.html in apache und gibt rechte
8) ./Graph.sh #erzeugt Graphen und kopiert sie ins ApacheDir /var/www/html/
9) pruefen anzeige www seite