INCLUDES=../../include
LIBS=../../lib
gyro: main.o
	gcc main.o -o gyro -L $(LIBS) -lsense -lm
main.o: main.c
	gcc -c main.c -I $(INCLUDES) 
clean:
	rm -f gyro *.o

