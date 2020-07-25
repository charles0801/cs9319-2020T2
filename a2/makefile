all: bwtdecode
bwtdecode: bwtdecode.o
	g++ -O3 bwtdecode.o -o bwtdecode

bwtdecode.o: bwtdecode.cpp
	g++ -c bwtdecode.cpp
clean:
	rm -f *.o *.out *.output bwtdecode