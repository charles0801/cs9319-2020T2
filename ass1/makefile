all: aencode adecode
aencode: aencode.o
	g++ aencode.o -o aencode -lmpfr -lgmp

aencode.o: aencode.cpp
	g++ -c aencode.cpp

adecode: adecode.o
	g++ adecode.o -g -o adecode -lmpfr -lgmp

adecode.o: adecode.cpp
	g++ -c adecode.cpp

clean:
	rm -f *.o adecode aencode