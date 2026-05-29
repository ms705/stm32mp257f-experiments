.PHONY: all clean

TOOLPREFIX := aarch64-linux-gnu-
CFLAGS := -mcpu=cortex-a35 -g
INCLUDE := -Iinc

all: kernel.elf

clean:
	rm *.o kernel.elf

kernel.elf: main.o uart.o startup.o gpio.o
	$(TOOLPREFIX)ld -T linker_sysram.ld $^ -o kernel.elf

startup.o: startup_el3.S
	$(TOOLPREFIX)gcc $(CFLAGS) $(INCLUDE) -c startup_el3.S -o startup.o

%.o: %.c
	$(TOOLPREFIX)gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

