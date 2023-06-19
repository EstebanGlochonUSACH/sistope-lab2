FLAGS = -Wall

main: lab2.c funciones.o
	gcc $(FLAGS) -o lab2 lab2.c funciones.o

funciones.o: funciones.c
	gcc -c $(FLAGS) funciones.c

clear:
	rm -f *.o lab2
