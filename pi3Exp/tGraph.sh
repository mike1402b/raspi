rrdtool graph tDay.png  -s 'now - 1 day' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen
cp tDay.png /var/www/html/


rrdtool graph tWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen

cp tWeek.png /var/www/html/


rrdtool graph tMonth.png  -s 'now - 1 month' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen

cp tMonth.png /var/www/html/


rrdtool graph tYear.png  -s 'now - 1 year' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:MIN \
  LINE1:temp0#0000FF:AussenMin \
  DEF:temp1=temperature.rrd:temp0:MAX \
  LINE2:temp1#FF0000:AussenMax




cp tYear.png /var/www/html/


