<head>
<meta name="viewport" content="width=device-width" />
<title>Wol</title>
</head>
Wol:</br></br>
<form method="get" action="wol.php">
<input type="submit" value="Lenovo" name="Lenovo">
<input type="submit" value="Hp" name="Hp">
</form>
<?php
$modeon18 = exec("gpio -g mode 23 out");
if(isset($_GET["Lenovo"])){
$val = exec("./wLenovo.sh");
echo "wol Lenovo:" . $val ;
}
else if(isset($_GET["Hp"])){
$val = exec("./wHp.sh");
echo "wol Hp:" . $val;
}

echo "<hr/>";

echo "Zeitstempel: " . date("d.m.Y H:i");


?>
</body>
</html>
