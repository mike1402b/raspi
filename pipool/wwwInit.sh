#give pi rights for writing in html
chown -cR pi:pi /var/www/html/

#copy index.html
cp index.php /var/www/html/
cp *.png /var/www/html/
cp piw /var/www/html/ -r

mv index.html bakIndex.html #damit index.php wirksam wird
