INCLUDES=../../include
LIBS=../../lib
simple: main.o
	gcc main.o -o simple -L $(LIBS) -lsense
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f simple *.o

