FLAGS = -Wall

main: lab2.c funciones.o
	gcc $(FLAGS) -o lab2 lab2.c funciones.o

funciones.o: funciones.c
	gcc -c $(FLAGS) funciones.c

broker: broker.c fbroker.o
	gcc $(FLAGS) -o broker broker.c fbroker.o

fbroker.o: fbroker.c
	gcc -c $(FLAGS) fbroker.c

worker: worker.c fworker.o
	gcc $(FLAGS) -o worker worker.c fworker.o

fworker.o: fworker.c
	gcc -c $(FLAGS) fworker.c

clear:
	rm -f *.o lab2 broker worker
