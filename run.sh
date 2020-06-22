
######################################################
# run sudo run.sh after make
# usage : run.sh [monitoring path]
#	ex) sudo run.sh /tmp/ (default /tmp/)
# 2017.02.23 written by sangsup.lee
######################################################
#!/bin/sh

CHSMACK="/usr/bin/chsmack"
SUDO="/usr/bin/sudo"
CONF="/tmp/hook.ini"
LOG_FILE="/tmp/file_log.txt"

if ! [ $(id -u) = 0 ]
then
	echo "[!] Must be run as root " 
	exit
fi

echo "[!] removing /tmp/file_log.txt."
rm -rf $LOG_FILE

echo "[!] Making /tmp/hook.ini"
rm $CONF && touch $CONF && chmod 777 $CONF

echo "[!] Saving argv1 into /tmp/hook.ini"
if [ $1 ] 
then echo "$1" > $CONF
fi

echo "[!] Creating /tmp/file_log.txt"
touch $LOG_FILE && chmod 777 $LOG_FILE

echo "[!] Inject libhook.so into /etc/ld.so.preload."
echo "[!] Must be off KUEP so that remount,rw /"
if test -e "$CHSMACK"
then
	chsmack -a "*" $LOG_FILE
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


echo "[!] Monitoring $LOG_FILE"
tail -f $LOG_FILE

