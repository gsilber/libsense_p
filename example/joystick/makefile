INCLUDES=../../include
LIBS=../../lib
joystick: main.o
	gcc main.o -o joystick -L $(LIBS) -lsense 
main.o: main.c
	gcc -c main.c -I $(INCLUDES)
clean:
	rm -f joystick *.o

