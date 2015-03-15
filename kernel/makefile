CC=i386-elf-gcc
LD=i386-elf-ld
NASM=nasm

all:kernel.bin

kernel.bin:kernel_entry.o kernel.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary
	mv *.bin ../build

kernel_entry.o:kernel_entry.asm
	$(NASM) -f elf $< -o $@

kernel.o:kernel.c
	$(CC) -ffreestanding -c $< -o $@ -I./console/

clean:
	rm *.o
