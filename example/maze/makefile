INCLUDES=../../include
LIBS=../../lib
maze: main.o
	gcc main.o -o maze -L $(LIBS) -lsense -lm
main.o: main.c
	gcc -c main.c -I $(INCLUDES)  -g
clean:
	rm -f maze *.o

