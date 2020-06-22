#MAKE FILE 

ARM_DIR     = /home/k1rh4/Android/Toolc/
ARM_TOOLS	= $(ARM_DIR)/bin/aarch64-linux-android-
ARM_CC      = $(ARM_TOOLS)gcc
SYS_ROOT	= --sysroot=$(ARM_DIR)/sysroot
RM 	= rm 
########################################################
CC 	= gcc
SYSROOT = 
#######################################################

PIC	= -c -fPIC 
SHARED	= -shared
DL	= -ldl
OPTION	= -Wl,--no-as-needed #-m32 

FILE 	= hook
#FILE	= test
default:
	$(CC) $(SYSROOT) $(PIC) $(FILE).c 
	$(CC) $(SYSROOT) $(OPTION) $(SHARED) $(FILE).o -o lib$(FILE).so $(DL)

ARM_LIBRARY:
	$(ARM_CC) $(SYS_ROOT) $(PIC) $(FILE).c 
	$(ARM_CC) $(SYS_ROOT) $(OPTION) $(SHARED) $(FILE).o -o lib$(FILE).so $(DL)

ARM_BINARY:
	$(ARM_CC) $(SYS_ROOT) $(OPTION) $(FILE).c -o $(FILE).bin

clean:
	$(RM) lib$(FILE).so $(FILE).o
