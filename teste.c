#include <stdio.h>
#include <stdlib.h>
#include "TP3.h"



int main(){
	FILE* entrada = fopen("entrada", "r");
	int n, i, result;
	int origem, destino;
	fscanf(entrada, "%d", &n);

	grafo* grafo = inicia_grafo(n);

	while(fscanf(entrada, "%d %d", &origem, &destino) > 0){
		add_aresta(grafo, origem, destino);
		//printf("%d %d\n", origem, destino);
	}
	//mostrar_matriz_adj(grafo);
	printf("\n");
	result = otimo(grafo);
	printf("s = %d\n", result);;
return 0;	
};