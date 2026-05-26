.PHONY: all clean

TOOLPREFIX := aarch64-none-elf-
CFLAGS := -mcpu=cortex-a35 -g

all: kernel.elf

clean:
	rm *.o kernel.elf

kernel.elf: main.o uart.o startup.o
	$(TOOLPREFIX)ld -T linker_sysram.ld $^ -o kernel.elf

startup.o: startup_el3.S
	$(TOOLPREFIX)gcc $(CFLAGS) -c startup_el3.S -o startup.o

%.o: %.c
	$(TOOLPREFIX)gcc $(CFLAGS) -c $< -o $@
