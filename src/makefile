#makefile
OBJS = mysh.o parse.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SUBS = mycat mycp myls
current = $(shell pwd)

all : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mysh
	make subsystem
	export PATH=$(current)/mycat:$(current)/mycp:$(current)/myls:$(PATH) ; echo "\n" ; ./mysh

mysh.o : mysh.c
	$(CC) $(CFLAGS) mysh.c

parse.o : parse.h parse.c
	$(CC) $(CFLAGS) parse.c

subsystem : 
	$(MAKE) -C mycat
	$(MAKE) -C mycp
	$(MAKE) -C myls

clean:
	\rm -f *.o mysh afile bfile
	cd mycat && $(MAKE) clean
	cd mycp && $(MAKE) clean
	cd myls && $(MAKE) clean

tar:
	tar cvzf proj2.tar.gz ./*

