#ifndef Grafo_H
#define Grafo_H

#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
	int* peso;
	int qtd_vertices;
	int** matriz_adjacencia;
}grafo;

grafo* inicia_grafo(int qtd_vertices);

void free_grafo(grafo* grafo, int qtd_vertices);
void add_aresta(grafo* grafo, int origem, int destino);
void remover_aresta(grafo* grafo, int origem, int destino);
void grafo_transposto(grafo* grafo);

#endif