INCLUDES=../../include
LIBS=../../lib
doomsday: main.o
	gcc main.o -o doomsday -L $(LIBS) -lsense
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f doomsday *.o

