# FileNotification

`FileNotification` 
FileNotification is one of the File access tracker.


## Why?

It's similer to inotifiy but inotify don't know who access file.
So, I made file notification for know who access files.


## What?

# k1rh4 @ k1rh4 in /k1rh4/DIY_DEVEL/FILEHOOK on git:master x [8:44:01] C:130
$ sudo ./run.sh 
[sudo] password for k1rh4: 
[!] removing /tmp/file_log.txt.
[!] Making /tmp/hook.ini
[!] Saving argv1 into /tmp/hook.ini
[!] Creating /tmp/file_log.txt
[!] Set authrization to /tmp/file_log.txt
[!] Inject libhook.so into /etc/ld.so.preload.
[!] Must be off KUEP so that remount,rw /
[!] Monitoring /tmp/file_log.txt
[+] Caller->ppName:[sh]:[4131],pName:[tail]:[4142]->/tmp/file_log.txt
[+] Caller->ppName:[-zsh]:[4175],pName:[touch]:[4208]->/tmp/testFile

# k1rh4 @ k1rh4 in /k1rh4/DIY_DEVEL/FILEHOOK on git:master x [8:44:01] C:130
$ sudo ./clean.sh 


## How?

```shell
git clone https://github.com/k1rh4/FileNotification.git
$make
$sudo ./ruh.sh

$sudo ./clean.sh
```

Contact.
k1rh4.lee@gmail.com 
