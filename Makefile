default:
	mkdir build
	cc multissh.c -o ./build/multissh

clean:
	rm -r ./build/

uninstall:
	sudo rm /usr/bin/multissh

install:
	sudo cp $(shell pwd)/build/multissh /usr/bin/multissh