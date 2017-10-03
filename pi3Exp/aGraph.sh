cd /home/pi/raspi/pi3Exp

rrdtool graph aDay.png  -s 'now - 1 day' -e 'now' \
  DEF:t0=solar.rrd:A0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=solar.rrd:A1:AVERAGE \
  LINE2:t1#0000FF:pool

cp aDay.png /var/www/html/

rrdtool graph aWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:t0=solar.rrd:A0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=solar.rrd:A1:AVERAGE \
  LINE2:t1#0000FF:pool

cp aWeek.png /var/www/html/

rrdtool graph aMonth.png  -s 'now - 1 month' -e 'now' \
  DEF:t0=solar.rrd:A0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=solar.rrd:A1:AVERAGE \
  LINE2:t1#0000FF:pool

cp aMonth.png /var/www/html/

rrdtool graph aYear.png  -s 'now - 1 year' -e 'now' \
  DEF:t0=solar.rrd:A0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=solar.rrd:A1:AVERAGE \
  LINE2:t1#0000FF:pool

cp aYear.png /var/www/html/

