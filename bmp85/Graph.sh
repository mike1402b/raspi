rrdtool graph Day.png  -s 'now - 1 day' -e 'now' \
  DEF:t0=temperature.rrd:t0:AVERAGE \
  LINE2:t0#00FF00:Temperatur 
#cp Day.png /var/www/html/

