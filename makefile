CC=gcc
CFLAGS = -g -Wall
LIBS = -lgmp

SOURCES = main.c keygen.c
OBJS = $(SOURCES:.c=.o)

all: bitsys

bitsys: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f  bitsys $(OBJS)
