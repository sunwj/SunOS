NASM=nasm

bootloader.bin:bootloader.asm
	$(NASM) -f bin $< -o $@
	mv *.bin ../build
