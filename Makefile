AR=ar
CC=gcc
CCFLAGS=-Wall
RM=rm -f

all: xcp

libxcpy.a: libxcpy.c libxcpy.h
	$(CC) $(CCFLAGS) -o libxcpy.o -c $<
	$(AR) r $@ libxcpy.o

xcp: xcp.c libxcpy.a
	$(CC) $(CCFLAGS) -o xcp $^

clean:
	$(RM) xcp libxcpy.a libxcpy.o

