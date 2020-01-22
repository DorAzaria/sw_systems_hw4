
CC=gcc
FLAG=-Wall
AR=ar
fPIC=-fPIC
all: main 

main: frequency.c
	$(CC) $(FLAG) frequency.c -g -o frequency
.PHONY:  frequency clean all
clean:
	rm -f *.o *.a *.so frequency
