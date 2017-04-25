rrdtool graph tDay.png  -s 'now - 1 day' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen
cp tDay.png /var/www/html/

rrdtool graph tWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen

cp tWeek.png /var/www/html/
