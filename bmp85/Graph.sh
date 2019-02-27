cd ~/raspi/bmp85

rrdtool graph Day.png  -s 'now - 1 day' -e 'now' \
  DEF:t2=bmp.rrd:t1:AVERAGE \
  LINE2:t2#FF0000:Luftdruck 
cp Day.png /var/www/html/

rrdtool graph Week.png  -s 'now - 1 week' -e 'now' \
  DEF:t2=bmp.rrd:t1:AVERAGE \
  LINE2:t2#FF0000:Luftdruck 
cp Week.png /var/www/html/

rrdtool graph Month.png  -s 'now - 1 month' -e 'now' \
  DEF:t2=bmp.rrd:t1:AVERAGE \
  LINE2:t2#FF0000:Luftdruck 
cp Month.png /var/www/html/

rrdtool graph Year.png  -s 'now - 1 year' -e 'now' \
  DEF:t2=bmp.rrd:t1:AVERAGE \
  LINE2:t2#FF0000:Luftdruck 
cp Year.png /var/www/html/
