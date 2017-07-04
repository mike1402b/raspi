cd /home/pi/raspi/pipool

rrdtool graph tDay.png  -s 'now - 1 day' -e 'now' \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:pool

cp tDay.png /var/www/html/

rrdtool graph tWeek.png  -s 'now - 1 week' -e 'now' \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:pool

cp tWeek.png /var/www/html/

rrdtool graph tMonth.png  -s 'now - 1 month' -e 'now' \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:pool

cp tMonth.png /var/www/html/

rrdtool graph tYear.png  -s 'now - 1 year' -e 'now' \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:pool

cp tYear.png /var/www/html/

