CC=i386-elf-gcc
LD=i386-elf-ld

INCLUDE=../kernel/

console.o: console.c
	$(CC) -ffreestanding -c $< -o $@ -I$(INCLUDE)

clean:
	rm *.o
