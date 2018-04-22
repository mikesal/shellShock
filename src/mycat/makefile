#makefile
OBJS = mycat.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mycat

mycat.o: mycat.c
	$(CC) $(CFLAGS) mycat.c

clean:
	\rm -f *.o mycat
