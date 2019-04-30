INCLUDES=../../include
LIBS=../../lib
simple: main.o
	gcc main.o -o mag -L $(LIBS) -lsense
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f mag *.o

