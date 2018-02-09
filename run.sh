
######################################################
# run sudo run.sh after make
# usage : run.sh [monitoring path]
#	ex) sudo run.sh /tmp/ (default /tmp/)
# 2017.02.23 written by sangsup.lee
######################################################
#!/bin/sh

CHSMACK="/usr/bin/chsmack"
SUDO="/usr/bin/sudo"

if ! [ $(id -u) = 0 ]
then
	echo "[!] Must be run as root " 
	exit
fi

echo "[!] removing /tmp/file_log.txt."
rm -rf /tmp/file_log.txt

echo "[!] Making /tmp/hook.ini"
rm /tmp/hook.ini
touch /tmp/hook.ini
chmod 777 /tmp/hook.ini

echo "[!] Saving argv1 into /tmp/hook.ini"
if [ $1 ] 
then echo "$1" > /tmp/hook.ini
fi

echo "[!] Creating /tmp/file_log.txt"
touch /tmp/file_log.txt

echo "[!] Set authrization to /tmp/file_log.txt"
chmod 777 /tmp/file_log.txt

echo "[!] Inject libhook.so into /etc/ld.so.preload."
echo "[!] Must be off KUEP so that remount,rw /"
if test -e "$CHSMACK"
then
	chsmack -a "*" /tmp/file_log.txt
	mount -o remount,rw /
fi

if test -e "$SUDO"
then sudo bash -c 'echo "$PWD/libhook.so" > /etc/ld.so.preload'
else bash -c 'echo "$PWD/libhook.so" > /etc/ld.so.preload'
fi

if test -e "$CHSMACK"
then 
	mount -o remount,ro /
fi
if ! [ `cat /etc/ld.so.preload` ]
then 
	echo "[e] Cant not write /etc/ld.so.preload"
	exit 
fi


echo "[!] Monitoring /tmp/file_log.txt"
tail -f /tmp/file_log.txt

