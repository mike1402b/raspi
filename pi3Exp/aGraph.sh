
rrdtool graph tDay.png  -s 'now - 1 day' -e 'now' \
  DEF:temp0=temperature.rrd:temp0:AVERAGE \
  LINE2:temp0#00FF00:Aussen
cp tDay.png /var/www/html/


rrdtool graph tWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:t0=temperature.rrd:temp0:MIN \
  LINE1:t0#0000FF:AussenMin \
  DEF:t1=temperature.rrd:temp0:AVERAGE \
  LINE2:t1#00FF00:AussenAvg \
  DEF:t2=temperature.rrd:temp0:MAX \
  LINE2:t2#FF0000:AussenMax
cp tWeek.png /var/www/html/


rrdtool graph tMonth.png  -s 'now - 1 month' -e 'now' \
  DEF:t0=temperature.rrd:temp0:MIN \
  LINE1:t0#0000FF:AussenMin \
  DEF:t1=temperature.rrd:temp0:AVERAGE \
  LINE2:t1#00FF00:AussenAvg \
  DEF:t2=temperature.rrd:temp0:MAX \
  LINE2:t2#FF0000:AussenMax
cp tMonth.png /var/www/html/


rrdtool graph tYear.png  -s 'now - 1 year' -e 'now' \
  DEF:t0=temperature.rrd:temp0:MIN \
  LINE1:t0#0000FF:AussenMin \
  DEF:t1=temperature.rrd:temp0:AVERAGE \
  LINE2:t1#00FF00:AussenAvg \
  DEF:t2=temperature.rrd:temp0:MAX \
  LINE2:t2#FF0000:AussenMax
cp tYear.png /var/www/html/