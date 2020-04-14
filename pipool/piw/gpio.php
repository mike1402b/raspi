<html>
<head>
<meta name="viewport" content="width=device-width" />
<title>gpio</title>
</head>
<body>
  <h1>gpio read</h1>
  <p>version vom 20190617 1352<br/>
    aktuelles Datum: <?php echo date("d.m.Y H:i:s"); ?>
  </P>
  <table border =1>
    <tr><td>18 =</td><td><?php echo exec("gpio -g read 18");?></td></tr>
    <tr><td>23 =</td><td><?php echo exec("gpio -g read 23");?></td><td>pumpe</td></tr>
    <tr><td>24 =</td><td><?php echo exec("gpio -g read 24");?></td></tr>
    <tr><td>25 =</td><td><?php echo exec("gpio -g read 25");?></td></tr>
  </table>
  <p>relay z.b. pumpe genau invers 0= ein, 1= aus </p>
</body>
