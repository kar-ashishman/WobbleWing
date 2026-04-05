CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CPU = cortex-m4
STD = gnu11
BOARD = netduinoplus2
INCLUDE = -I ./HAL/Include -I ../FreeRTOS/Include
ARCHIVES = ../FreeRTOS/FreeRTOS.a ./HAL/hal.a
CFLAGS = -mthumb -mcpu=$(CPU) -g -c $(INCLUDE) -Wall -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g -c
LDFLAGS_QEMU = -T rom_qemu.ld -Map=final_qemu.map
LDFLAGS_TARGET = -T rom_target.ld -Map=final.map

SRC = startup.c
OBJ = $(patsubst %.c,%.o,$(SRC))

final.elf : $(OBJ) rom_target.ld
	$(LD) $(LDFLAGS_TARGET) -o $@ $(OBJ) $(ARCHIVES)
	arm-none-eabi-objdump -D -S $@ > final.elf.lst
	arm-none-eabi-readelf -a $@ > final.elf.debug

final_qemu.elf : $(OBJ) rom_qemu.ld
	$(LD) $(LDFLAGS_QEMU) -o $@ $(OBJ) $(ARCHIVES)
	arm-none-eabi-objdump -D -S $@ > final_qemu.elf.lst
	arm-none-eabi-readelf -a $@ > final_qemu.elf.debug

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@


qemu :
	qemu-system-arm -S -M $(BOARD) -nographic -cpu $(CPU) -kernel final.elf -gdb tcp::1234

gdb :
	gdb-multiarch -q final.elf -ex "target remote localhost:1234"

.PHONY : clean

clean :
	rm -f *.o *.elf *.map *.lst *.debug