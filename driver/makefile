CC=i386-elf-gcc
LD=i386-elf-ld
INCULDE=-I./ -I../include/ -I../kernel/

console.o:console.c
	$(CC) -ffreestanding -c $< -o $@ $(INCULDE)

clean:
	rm *.o
