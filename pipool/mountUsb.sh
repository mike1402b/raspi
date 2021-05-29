#meist sda1 oder sdb1 gerätename
#mit blkid kiegt man die id
mount -t vfat -o utf8,uid=pi,gid=pi,noatime /dev/sda1 /media/usbstick

