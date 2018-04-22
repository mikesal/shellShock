#makefile
OBJS = mycp.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mycp

mycp.o: mycp.c
	$(CC) $(CFLAGS) mycp.c

clean:
	\rm -f *.o mycp