#
#	MAKEFILE FOR HI-TECH COMPILER
#	MCU = PIC16F73
#

#SRC = tone
#SRC = pwmaudio
SRC = soundTest
PRJ = sounds
MCU = 16F73
CC = picc.exe

CFLAGS = -q -g -P --char=unsigned --asmlist --chip=$(MCU) 
CFLAGS += --errformat="%f:%l: Error: %s"  
CFLAGS += --warnformat="%f:%l: Warning: %s"
CFLAGS += -I"../../include" -I"../"



all:
	$(CC) $(CFLAGS) -C $(SRC).c
	$(CC) $(CFLAGS) -o$(PRJ).cof -m$(PRJ).map $(SRC).obj  

clean:
	rm -rf *.obj *.rlf *.sdb *.lst *.cof *.hxl *.map *.sym *.hex
	


