os-img:./build/bootloader.bin ./build/kernel.bin
	cat $^ > $@

./build/bootloader.bin:
	make -C ./boot/makefile

./build/kernel.bin:
	make -C ./kernel/makefile

clean:
	rm os-img
