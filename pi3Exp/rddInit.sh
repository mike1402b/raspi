:
echo "Erzeuge rdd Datenbank fuer 10 Werte, 100 Tage aufbewahrung viertelstuendlicher AVG  100 Jahre aufbewahrung min /max / avg"

#step 900 sec (60*15=900) alle viiertelstunden
#DS Datasource:name:GAUGE:heartbeat 20min=1200sec:min::max
#RRA RoundRobinArchive alle 9600 Zeilen (pro Tag 96 Zeilen (=24*4)
# 100 Jahre aufbewahrung min, max, AVG

rrdtool create solar.rrd --step 900 \
DS:A0:GAUGE:1200:-50:200 \
DS:A1:GAUGE:1200:-50:200 \
DS:A2:GAUGE:1200:-50:200 \
DS:A3:GAUGE:1200:-50:200 \
DS:A4:GAUGE:1200:-50:200 \
DS:A5:GAUGE:1200:-50:200 \
DS:A6:GAUGE:1200:-50:200 \
DS:A7:GAUGE:1200:-50:200 \
RRA:AVERAGE:0.5:1:9600 \
RRA:MIN:0.5:96:36000 \
RRA:MAX:0.5:96:36000 \
RRA:AVERAGE:0.5:96:36000

