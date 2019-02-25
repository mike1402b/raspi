rrdtool graph Day.png  -s 'now - 1 day' -e 'now' \
  DEF:t0=bmp.rrd:t1:AVERAGE \
  LINE2:t0#00FF00:Temperatur \
  DEF:t1=bmp.rrd:t0:AVERAGE \
  LINE2:t1#0000FF:Luftdruck \
  DEF:t2=bmp.rrd:t2:AVERAGE \
  LINE2:t2#FF0000:Hoehe 
cp Day.png /var/www/html/

