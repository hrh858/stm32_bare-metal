CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=c11 -O0

all:main.o

main.o:src/main.c
	$(CC) $(CFLAGS) $^ -o $@
