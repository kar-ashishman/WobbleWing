CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CPU = cortex-m3
STD = gnu11
BOARD = stm32vldiscovery
CFLAGS = -mthumb -mcpu=$(CPU) -g -c

SRC = $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))


FreeRTOS.a : $(OBJ)
	ar rcs $@ $^

%.o : %.c
	$(CC) -I ./Include $(CFLAGS) $< -o $@

cleanobjects :
	rm -f *.o