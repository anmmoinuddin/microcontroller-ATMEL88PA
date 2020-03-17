################################################################################
# Makefile for MyAVR Programm                                                  #
# First test program                                                           #
################################################################################


# Options ######################################################################
PORT=COM6
PROGRAMMER=avr911
TARGET_CPU=atmega88pa
TARGET_PROCESSOR=m88p
CFLAGS=-Wall -O3 -c -mmcu=$(TARGET_CPU)
LDFLAGS=-O3 -mmcu=$(TARGET_CPU) -o
COM_PORT=/dev/ttyUSB_uart
COM_SPEED=9600

# Program ######################################################################
all: main.hex

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o lcd.o uart.o
	avr-gcc  $(LDFLAGS) main.elf main.o lcd.o uart.o

main.o: main.c
	avr-gcc  $(CFLAGS) main.c

lcd.o: lcd.c lcd.h
	avr-gcc $(CFLAGS) lcd.c

uart.o: uart.c uart.h
	avr-gcc $(CFLAGS) uart.c

program: main.hex
	avrdude -P $(PORT) -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -Uflash:w:main.hex:i


# Fuses ########################################################################
checkfuse:
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U lfuse:r:-:i -U hfuse:r:-:i 


setfuses:
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U lfuse:w:0xFF:m
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U hfuse:w:0xD7:m

# Debug ########################################################################
debug:
	gtkterm -p $(COM_PORT) -s $(COM_SPEED) &

# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~ *.bak
