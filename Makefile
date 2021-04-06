# Very First Simple Makefile

# Compiler 
CC=gcc
TARGET=doit


all:	doit.o 
	$(CC) doit.c -o $(TARGET).o

clean:
	rm *.o 
