ASM=nasm

bootloader.bin:bootloader.asm
	$(ASM) -f bin $< -o $@
	mv *.bin ../build
