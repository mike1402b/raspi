
rrdtool graph aDay.png  -s 'now - 1 day' -e 'now' \
  DEF:A0=solar.rrd:A0:AVERAGE \
  LINE2:A0#00FF00:Avg
cp aDay.png /var/www/html/


rrdtool graph aWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:A0=solar.rrd:A0:MIN \
  LINE1:t0#0000FF:Min \
  DEF:t1=solar.rrd:A0:AVERAGE \
  LINE2:t1#00FF00:Avg \
  DEF:t2=solar.rrd:A0:MAX \
  LINE2:t2#FF0000:Max
cp aWeek.png /var/www/html/


rrdtool graph aMonth.png  -s 'now - 1 month' -e 'now' \
  DEF:A0=solar.rrd:A0:MIN \
  LINE1:t0#0000FF:Min \
  DEF:A1=solar.rrd:A0:AVERAGE \
  LINE2:t1#00FF00:Avg \
  DEF:t2=solar.rrd:A0:MAX \
  LINE2:t2#FF0000:Max
cp aMonth.png /var/www/html/


rrdtool graph aYear.png  -s 'now - 1 year' -e 'now' \
  DEF:t0=solar.rrd:A0:MIN \
  LINE1:t0#0000FF:Min \
  DEF:t1=solar.rrd:A0:AVERAGE \
  LINE2:t1#00FF00:Avg \
  DEF:t2=solar.rrd:A0:MAX \
  LINE2:t2#FF0000:Max
cp aYear.png /var/www/html/
