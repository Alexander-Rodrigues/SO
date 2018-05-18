CC=gcc
CFLAGS=-Wall
CFILES=$(wildcard *.c)
OFILES=$(CFILES:.c=.o)

reader: $(CFILES)
	$(CC) $(CFILES) -o $(OFILES) $(CFLAGS)
