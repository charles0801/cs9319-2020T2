all: bwtdecode fileio

fileio: fileio.o
	g++ fileio.o -o fileio

fileio.o: fileio.cpp
	g++ -c fileio.cpp

bwtdecode: bwtdecode.o
	g++ -O3 bwtdecode.o -o bwtdecode

bwtdecode.o: bwtdecode.cpp
	g++ -c bwtdecode.cpp
clean:
	rm -f *.o *.out *.output bwtdecode memory.txt
	 