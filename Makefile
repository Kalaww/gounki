CC=gcc
CFLAGS=-std=c89 -Wall -pedantic -g
LDFLAGS=
EXEC=test
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all : $(EXEC)

test : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
