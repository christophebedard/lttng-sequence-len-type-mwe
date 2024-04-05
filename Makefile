all:
	cd lib && make && cd ..
	cd app && make && cd ..

clean:
	cd lib && make clean && cd ..
	cd app && make clean && cd ..
