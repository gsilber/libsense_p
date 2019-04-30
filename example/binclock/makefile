INCLUDES=../../include
LIBS=../../lib
binclock: main.o
	gcc main.o -o binclock -L $(LIBS) -lsense
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f binclock *.o

