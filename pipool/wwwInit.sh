#give pi rights for writing in html
chown -c pi:root /var/www/html/

#copy index.html
cp index.php /var/www/html/
cp *.png /var/www/html/
cp piw /var/www/html/ -r

