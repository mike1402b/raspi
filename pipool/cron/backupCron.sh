#erfordert root rechte
cp /var/spool/cron/crontabs/* /home/pi/raspi/pipool/cron
#cron dateien haben keine rechte, setzte diese um  git backup machen zu können
sudo chmod 774 /home/pi/raspi/pipool/cron/*
