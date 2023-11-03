CC = gcc
CFLAGS = -Wall -g
LIBS = -lgmp

SOURCES1 = keygen.c rsa_assign_1.c endec.c  
SOURCES2 = keygen.c dh_assign_1.c endec.c  

OBJS1 = $(SOURCES1:.c=.o)
OBJS2 = $(SOURCES2:.c=.o)


all: rsa_assign_1 dh_assign_1

rsa_assign_1: $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dh_assign_1: $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ 

clean:
	rm -f  rsa_assign_1  dh_assign_1 private* public* performance.txt $(OBJS1) $(OBJS2)

