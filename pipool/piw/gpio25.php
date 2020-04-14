<html>
<head>
<meta name="viewport" content="width=device-width" />
<title>Schalter</title>
</head>
GPIO 25 schalten:
<form method="get" action="gpio25.php">
<input type="submit" value="Licht ein" name="Lichtein">
<input type="submit" value="Licht aus" name="Lichtaus">
</form>
<?php
$modeon18 = exec("gpio -g mode 25 out");
if(isset($_GET["Lichtein"])){
$val = exec("gpio -g write 25 1");
echo "Licht an";
}
else if(isset($_GET["Lichtaus"])){
$val = exec("gpio -g write 25 0");
echo "Licht aus";
}

echo "<hr/>";
$val = exec("gpio -g read 25");
echo " gpio25 = $val ";
echo " <hr />"


?>
</body>
</html>
