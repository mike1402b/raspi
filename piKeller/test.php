<?php

echo "Zeitstempel: " . date("d.m.Y H:i") . "<hr />";

$val=exec("/var/www/html/wLenovo.sh");
echo $val;
echo "<hr />";

echo "Zeitstempel: " . date("d.m.Y H:i");



?>
