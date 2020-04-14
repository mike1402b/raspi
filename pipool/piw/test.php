<?php
echo "test<hr />";
$val="mytest";
$val=exec("ls");
$val=exec("gpio read 23");
echo $val;
echo "<hr />";
?>
