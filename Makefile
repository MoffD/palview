CC=gcc
CFLAGS=-lSDL -I.

palview: palview.c 
	$(CC) $(CFLAGS) -o palview palview.c tinyfiledialogs.c
