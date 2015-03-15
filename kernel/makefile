CC=i386-elf-gcc
LD=i386-elf-ld
NASM=nasm

INCLUDE=-I./ -I../driver/

all:kernel.bin

kernel.bin:kernel_entry.o kernel.o port_io.o ../driver/*.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary
	mv *.bin ../build

kernel_entry.o:kernel_entry.asm
	$(NASM) -f elf $< -o $@

kernel.o:kernel.c
	$(CC) -ffreestanding -c $< -o $@ $(INCLUDE)

port_io.o:port_io.c
	$(CC) -ffreestanding -c $< -o $@

../driver/*.o:
	make -C ../driver/makefile

clean:
	rm *.o
