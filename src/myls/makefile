#makefile
OBJS = myls.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o myls

myls.o: myls.c
	$(CC) $(CFLAGS) myls.c

clean:
	\rm -f *.o myls