default: clean
	mkdir build
	cc multissh.c -o ./build/multissh

clean:
	rm -r ./build/

clean-link:
	sudo rm /usr/bin/multissh

install:
	sudo ln -s $(shell pwd)/build/multissh /usr/bin/multissh