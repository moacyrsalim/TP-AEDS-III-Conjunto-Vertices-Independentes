all: tp3

tp3: main.o grafo.o TP3.o tempo.o
	gcc -o tp3 main.o grafo.o TP3.o tempo.o

main.o: main.c grafo.h TP3.h
	gcc -c main.c

grafo.o: grafo.c grafo.h
	gcc -c grafo.c

TP3.o: TP3.c TP3.h 
	gcc -c TP3.c

tempo.o: tempo.c tempo.h
	gcc -c tempo.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf tp3 