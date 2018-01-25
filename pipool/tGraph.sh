cd /home/pi/raspi/pipool

rrdtool graph tDay.png  -s 'now - 1 day' -e 'now' -w 400 -h 200 \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:poolU \
  DEF:t2=temp.rrd:t2:AVERAGE \
  LINE2:t2#000077:poolO 
  
cp tDay.png /var/www/html/

rrdtool graph tWeek.png  -s 'now - 1 week' -e 'now' -w 400 -h 200 \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:poolU \
  DEF:t2=temp.rrd:t2:AVERAGE \
  LINE2:t2#000077:poolO 

cp tWeek.png /var/www/html/

rrdtool graph tMonth.png  -s 'now - 1 month' -e 'now' -w 400 -h 200 \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:poolU \
  DEF:t2=temp.rrd:t2:AVERAGE \
  LINE2:t2#000077:poolO 

cp tMonth.png /var/www/html/

rrdtool graph tYear.png  -s 'now - 1 year' -e 'now' -w 400 -h 200 \
  DEF:t0=temp.rrd:t0:AVERAGE \
  LINE2:t0#FF0000:pi \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar \
  DEF:t7=temp.rrd:t7:AVERAGE \
  LINE2:t7#00FFAA:aussen \
  DEF:t1=temp.rrd:t1:AVERAGE \
  LINE2:t1#0000FF:poolU \
  DEF:t2=temp.rrd:t2:AVERAGE \
  LINE2:t2#000077:poolO 

  
cp tYear.png /var/www/html/

#---------------------------- 2. Diagramm -------------------------------

rrdtool graph tDayAll.png  -s 'now - 1 day' -e 'now' -w 400 -h 200 \
  DEF:t3=temp.rrd:t3:AVERAGE \
  LINE2:t3#00FF00:erdeU \
  DEF:t4=temp.rrd:t4:AVERAGE \
  LINE2:t4#009900:erdeO \
  DEF:t5=temp.rrd:t5:AVERAGE \
  LINE2:t5#FF0000:kisteU \
  DEF:t6=temp.rrd:t6:AVERAGE \
  LINE2:t6#ffc0c0:kisteO \
  DEF:t7=temp.rrd:t7:AVERAGE \
  LINE2:t7#00FFAA:aussen 
  
cp tDayAll.png /var/www/html/


rrdtool graph tWeekAll.png  -s 'now - 1 week' -e 'now' -w 400 -h 200 \
  DEF:t3=temp.rrd:t3:AVERAGE \
  LINE2:t3#00FF00:erdeU \
  DEF:t4=temp.rrd:t4:AVERAGE \
  LINE2:t4#001100:erdeO \
  DEF:t5=temp.rrd:t5:AVERAGE \
  LINE2:t5#AAFF00:kisteU \
  DEF:t6=temp.rrd:t6:AVERAGE \
  LINE2:t6#55AA00:kisteO \
  DEF:t7=temp.rrd:t7:AVERAGE \
  LINE2:t7#00FFAA:aussen \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar 
  
cp tWeekAll.png /var/www/html/

rrdtool graph tMonthAll.png  -s 'now - 1 month' -e 'now' -w 400 -h 200 \
  DEF:t3=temp.rrd:t3:AVERAGE \
  LINE2:t3#00FF00:erdeU \
  DEF:t4=temp.rrd:t4:AVERAGE \
  LINE2:t4#001100:erdeO \
  DEF:t5=temp.rrd:t5:AVERAGE \
  LINE2:t5#AAFF00:kisteU \
  DEF:t6=temp.rrd:t6:AVERAGE \
  LINE2:t6#55AA00:kisteO \
  DEF:t7=temp.rrd:t7:AVERAGE \
  LINE2:t7#00FFAA:aussen \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar 
  
cp tMonthAll.png /var/www/html/

rrdtool graph tYearAll.png  -s 'now - 1 year' -e 'now' -w 400 -h 200 \
  DEF:t3=temp.rrd:t3:AVERAGE \
  LINE2:t3#00FF00:erdeU \
  DEF:t4=temp.rrd:t4:AVERAGE \
  LINE2:t4#001100:erdeO \
  DEF:t5=temp.rrd:t5:AVERAGE \
  LINE2:t5#AAFF00:kisteU \
  DEF:t6=temp.rrd:t6:AVERAGE \
  LINE2:t6#55AA00:kisteO \
  DEF:t7=temp.rrd:t7:AVERAGE \
  LINE2:t7#00FFAA:aussen \
  DEF:t8=temp.rrd:t8:AVERAGE \
  LINE2:t8#AA0000:solar 
  
cp tYearAll.png /var/www/html/
