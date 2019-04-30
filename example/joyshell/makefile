INCLUDES=../../include
LIBS=../../lib
joyshell: main.o
	gcc main.o -o joyshell -L $(LIBS) -lsense 
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f joyshell *.o

