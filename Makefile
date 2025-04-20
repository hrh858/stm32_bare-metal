CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=c11 -Wall -O0

all:main.o startup.o

main.o:src/main.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:src/startup.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf
