all:depend
	cat ./build/bootloader.bin ./build/kernel.bin > os-img

depend:
	make -C ./boot/
	make -C ./driver/
	make -C ./kernel/

clean:
	rm os-img
	rm ./build/*.*

dep_clean:
	rm ./driver/*.o
	rm ./kernel/*.o
