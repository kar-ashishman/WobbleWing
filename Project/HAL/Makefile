CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CPU = cortex-m4
STD = gnu11
CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g -c

SRC = $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))


hal.a : $(OBJ)
	ar rcs $@ $^

%.o : %.c
	$(CC) -I ./Include $(CFLAGS) $< -o $@

cleanobjects :
	rm -f *.o