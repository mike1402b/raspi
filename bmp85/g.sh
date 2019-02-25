rrdtool graph Day.png  -s 'now - 1 day' -e 'now' \
  DEF:t0=bmp.rrd:t1:AVERAGE \
  LINE2:t0#00FF00:t1 
cp Day.png /var/www/html/

