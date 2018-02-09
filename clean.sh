#!/bin/sh

CHSMACK="/usr/bin/chsmack"

if ! [ $(id -u) = 0 ]
then
	echo "[!] Must be run as root " 
	exit
fi

if test -e "$CHSMACK"
then 
	mount -o remount,rw /
fi

if test -e "$SUDO"
then 
	sudo rm /etc/ld.so.preload
else
	rm /etc/ld.so.preload
fi

if test -e "$CHSMACK"
then 
	mount -o remount,ro /
fi

