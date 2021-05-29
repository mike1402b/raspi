apt update
#apt install xrdp
apt install apache2 php libapache2-mod-php -y
apt install rrdtool
apt install python-rrdtool

mkdir /home/pi/log
chown pi:pi /home/pi/log
chmod 774 /home/pi/log

#anschließend www-init ausführen
#tGraph.sh => sollte bilder im www aktualisieren
#gettemp.py => sollte sendoren auslesen
