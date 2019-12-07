#include "grafo.h"

grafo* inicia_grafo(int qtd_vertices){
	int i;
	grafo* grafo = malloc(sizeof(grafo));

	grafo->qtd_vertices = qtd_vertices;

	grafo->peso = calloc(qtd_vertices, sizeof(int));
	grafo->matriz_adjacencia = (int**)malloc((qtd_vertices+1)*sizeof(int*));
	
	for (i=0; i < qtd_vertices; i++)
		grafo->matriz_adjacencia[i] = (int*)calloc(qtd_vertices, sizeof(int));
	
	return grafo;
}

void free_grafo(grafo* grafo, int qtd_vertices){
	int i;
	for(i=0; i <= qtd_vertices; i++){
		free(grafo->matriz_adjacencia[i]);
	}
	free(grafo->matriz_adjacencia);
	free(grafo->peso);
}

void add_aresta(grafo* grafo, int origem, int destino){
	if (grafo->matriz_adjacencia[origem][destino] == 1){
		printf("A aresta já existe.\n");
		return;
	}

	grafo->matriz_adjacencia[origem][destino] = 1;
	grafo->matriz_adjacencia[destino][origem] = 1;
}

void remover_aresta(grafo* grafo, int origem, int destino){
	if (grafo->matriz_adjacencia[origem][destino] == 0){
		printf("A aresta não existe.\n");
		return;
	}
	grafo->matriz_adjacencia[origem][destino] = 0;
	grafo->matriz_adjacencia[destino][origem] = 0;
}


void grafo_transposto(grafo* grafo){
	int i, j;
	for (i=1; i<=grafo->qtd_vertices; i++){
		for (j=1; j<=grafo->qtd_vertices; j++){
			if(grafo->matriz_adjacencia[i][j] == 0)
				grafo->matriz_adjacencia[i][j] = 1;
			else
				grafo->matriz_adjacencia[i][j] = 0;
		}
	}
}