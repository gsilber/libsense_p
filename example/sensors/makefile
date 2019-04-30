INCLUDES=../../include
LIBS=../../lib
sensors: main.o
	gcc main.o -o sensors -L $(LIBS) -lsense
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f sensors *.o

