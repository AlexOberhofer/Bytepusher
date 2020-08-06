CC=gcc
CLAGS=-I. -I./include -Wall 
DEPS=sys.h

ENGINEOBJS=./src/engine/bytepusher.o
SYSOBJS=./src/sys/sdl.c



.c.o: ($DEPS)
	$(CC) -I./include/ -c -std=c89 $< -o $@ $(CFLAGS)

bp: $(ENGINEOBJS) $(SYSOJBS)
	$(CC) $(CFLAGS) -std=c89 -o bp $(ENGINEOBJS) $(SYSOBJS) -lSDL2

clean:
	rm bp