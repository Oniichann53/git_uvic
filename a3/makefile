#
# "makefile" for the third implementation of "icsout" (icsout3)
# Spring 2021, assignment #3)
#

CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#
#CFLAGS=-c -Wall -g -DDEBUG -std=c99
CFLAGS=-c -Wall -g -std=c99

process_cal3: process_cal3.o listy.o emalloc.o
	$(CC) process_cal3.o listy.o emalloc.o -o process_cal3

process_cal3.o: process_cal3.c listy.h ics.h emalloc.h
	$(CC) $(CFLAGS) process_cal3.c

listy.o: listy.c listy.h ics.h emalloc.h
	$(CC) $(CFLAGS) listy.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o process_cal3
