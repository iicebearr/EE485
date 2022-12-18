OBJFILES = add.o multiply.o pow.o polynomial.o
EXECUTABLE = polynomial
CC = gcc
CFLAGS = -Wall -Werror
CPPFLAGS = -I include

vpath %.c src
vpath %.h include

all: $(OBJFILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJFILES) -o $(EXECUTABLE)
add.o: add.c add.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^
multiply.o: multiply.c multiply.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^
pow.o: pow.c pow.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^
polynomial.o: polynomial.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^
clean:
	rm -f *.o *~ $(EXECUTABLE) include/*.gch

.PHONY: test

test:
   ./$(EXECUTABLE) < input.txt > result.txt
   diff result.txt answer.txt