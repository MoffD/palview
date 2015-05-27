CC=gcc
CFLAGS=-lSDL

palview: palview.c 
	$(CC) $(CFLAGS) -o palview palview.c
