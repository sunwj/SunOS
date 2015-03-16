CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm

INCLUDE=-I./ -I../include/ -I../driver/
OBJS=kernel_entry.o kernel.o port_io.o ../driver/console.o

all:kernel.bin
	mv kernel.bin ../build/

kernel.bin:$(OBJS)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o:kernel_entry.asm
	$(ASM) -f elf $< -o $@

%.o: %.c
	$(CC) -ffreestanding -c $< -o $@ $(INCLUDE)

clean:
	rm *.o
