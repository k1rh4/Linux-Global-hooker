#MAKE FILE 

TIZEN_DIR       = /usr/
TIZEN_CC        = $(TIZEN_DIR)/bin/arm-linux-gnueabi-gcc-4.9

RM 	= rm 
########################################################
CC 	= gcc
SYSROOT = 
#CC      = $(TIZEN_CC)
#SYSROOT = $(TIZEN_SYSROOT)
#######################################################

PIC	= -c -fPIC 
SHARED	= -shared #-m32
DL	= -ldl 
OPTION	=-Wimplicit-function-declaration

FILE 	= hook

default:
	$(CC) $(SYSROOT) $(OPTION) $(PIC) $(FILE).c 
	$(CC) $(SYSROOT) $(OPTION) $(SHARED) $(FILE).o -o lib$(FILE).so $(DL)

clean:
	$(RM) lib$(FILE).so $(FILE).o
