CC=gcc
CLAGS=-I. -I./include -std=c89 -Wall 
DEPS=sys.h

ENGINEOBJS=./src/engine/bytepusher.c
SYSOBJS=./src/sys/sdl.c



.c.o: ($DEPS)
	$(CC) -I./include/ -c $< -o $@ $(CFLAGS)

bp: $(ENGINEOBJS) $(SYSOJBS)
	$(CC) $(CFLAGS) -o bp $(ENGINEOBJS) $(SYSOBJS) -lSDL2

clean:
	rm bp