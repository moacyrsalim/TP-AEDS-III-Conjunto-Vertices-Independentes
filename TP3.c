#include <stdio.h>
#include <getopt.h>
#include "TP3.h"


int get_parametros(char **entrada, char **saida, int argc, char **argv){
	int opt;
	while ((opt = getopt(argc, argv, "i:o:12")) > 0){
		switch (opt){
			case 'i':
				*entrada = optarg;
				break;

			case 'o':
				*saida = optarg;
				break;

			case '1':
				return 1;

			case '2':
				return 2;

			default: printf("Diretiva não reconhecida.\n");
		}
	}
	return 0;
}

int executar(int argc, char** argv, char** saida){
	FILE* input;
	FILE* tempus = fopen("tempo", "w");
	char* entrada;
	int opt, result, vertices;
	int origem, destino;
	double tempo, tempo_u, tempo_s;
	grafo* grafo;

	opt = get_parametros(&entrada, saida, argc, argv);

	input = fopen(entrada, "r");

	tempo = time_start();
	tempo_u = user_time_start();
	tempo_s = system_time_start();

	fscanf(input, "%d", &vertices);
	grafo = inicia_grafo(vertices);
	
	while(fscanf(input, "%d %d", &origem, &destino) > 0){
		add_aresta(grafo, origem, destino);
	}

	if(opt == 0){
		result = otimo(grafo);
		tempo_u = user_time_end(tempo_u);
		tempo_s = system_time_end(tempo_s);
		tempo = time_end(tempo);
		fprintf(tempus, "    Tempos:\nExecução: %f\nUsuário: %f\nSistema:% f\n", tempo, tempo_u, tempo_s);
		return result;
	}

	if(opt == 1){
		result = heuristica1(grafo);
		tempo_u = user_time_end(tempo_u);
		tempo_s = system_time_end(tempo_s);
		tempo = time_end(tempo);
		fprintf(tempus, "    Tempos:\nExecução: %f\nUsuário: %f\nSistema:%f\n", tempo, tempo_u, tempo_s);
		return result;
	}

	if(opt == 2){
		result = heuristica2(grafo);
		tempo_u = user_time_end(tempo_u);
		tempo_s = system_time_end(tempo_s);
		tempo = time_end(tempo);
		fprintf(tempus, "    Tempos:\nExecução: %f\nUsuário: %f\nSistema:%f\n", tempo, tempo_u, tempo_s);
		return result;
	}
	return -1;
}

int existe_v(int vertice, int* conjunto){
	int i;	
	while(conjunto[i] != -2){
		if (conjunto[i] == vertice)
			return 1;
		
		i++;
	}
	return 0;
}

int verificar_adj(int v, int* solution, grafo* grafo){
	int i;
	int x;
	for(i = 0; i < grafo->qtd_vertices; i++){
		if (solution[i] == -1){
			break;
		}
		if (grafo->matriz_adjacencia[v][i] == 1){
			return 1;
		}
	}
	return 0;
}

void ponderar(grafo* grafo){
	int i, j;
	for(i = 0; i < grafo->qtd_vertices; i++){
		for(j = i; j < grafo->qtd_vertices; j++){
			if(grafo->matriz_adjacencia[i][j] == 1){
				grafo->peso[i]++;
				grafo->peso[j]++;
			}
		}
	}
}

void esvaziar_vet(int *vetor, int tamanho){
	int i;
	for (i = 0; i < tamanho; i++){
		vetor[i] = -1;
	}
}

void reduzir_matriz(int** matriz, grafo* grafo){
	int i, j;
	int cont;
	
	for( i= 0; i < grafo->qtd_vertices; i++){
		for(j = 0; j < grafo->qtd_vertices; j++){
			matriz[i][j] = -1;
		}
	}

	for(i = 0; i < grafo->qtd_vertices; i++){
		cont = 0;
		for(j = 0; j < grafo->qtd_vertices; j++){
			if(grafo->matriz_adjacencia[i][j] == 1){
			matriz[i][cont] = j;
			cont++;
			}
		}
	}
}

void ordenar(int *vetor, int tamanho){
	int i, j;
	int aux;
	for(i = 0; i < tamanho; i++){
		for(j = i; j < tamanho; j++){
			if (vetor[i] > vetor[j]){
				aux = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = aux;
			}
		}
	}
}

int max(int* vetor, int tamanho){
	int max = vetor[0];
	for(int i = 0; i < tamanho; i++){
		if(vetor[i] > max)
			max = vetor[i];
	}
	return max;
}

int verifica_vet_vazio(int* solution, int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(solution[i] != -1)
			return 0;
	}
	return 1;
}

int** aloca_matriz(int n){
	int i;
	int** matriz = malloc(n*sizeof(int*));
	for(i = 0; i < n; i++)
		matriz[i] = malloc(n*sizeof(int));

	return matriz;
}

int heuristica1(grafo* grafo){
	int i, x = 0;
	int *solution = malloc(grafo->qtd_vertices*sizeof(int));
	esvaziar_vet(solution, grafo->qtd_vertices);
	ponderar(grafo);

	ordenar(grafo->peso, grafo->qtd_vertices);

	for(i = 0; i < grafo->qtd_vertices; i++){
		if(verificar_adj(i, solution, grafo)){
			continue;
		}
		solution[x] = i;
		x++;
	}

	return x;
}

int heuristica2(grafo* grafo){
	int i, j;
	int x;
	int **aux = aloca_matriz(grafo->qtd_vertices);

	for(i = 0; i < grafo->qtd_vertices; i++)
		grafo->peso[i] = 1;
	
	reduzir_matriz(aux, grafo);
	
	for (i=0; i<grafo->qtd_vertices; i++){
		for(j = 0; aux[i][j]!= -1; j++){
			x = aux[i][j];
			if(grafo->peso[i] == grafo->peso[x]){
				grafo->peso[i]++;
				j = -1;
			}
		}
	}
	return max(grafo->peso, grafo->qtd_vertices);

}

int pseudo_cor(int* peso, int cores){
	int* s = calloc(cores, sizeof(int));
	int x;
	for(int i = 0; i< cores; i++){
		x = peso[i];
		s[x-1]++;
	}
	return max(s, cores);
}

int otimo(grafo* grafo){
	int t = grafo->qtd_vertices;
	int* s = malloc(t*sizeof(int));
	for(i = 1; i < t; i++){
			e
		do(){
			if(verifica_cover(grafo, s))
				return s;
		}while(1);
	}
}
int verifica_cover(grafo* grafo, int* s){

}

int tam_v(int* v, int t){
	int t = 0;
	for(int i = 0; i < t; i++){
		if(t != -1)
			t++;
	}
	return t;
}

void mostrar_vetor(int* v, int tamanho){
	int i;
	for(i=0; i<tamanho; i++){
		printf("% -2d ", v[i]);
	}
	printf("\n");
}

void mostrar_matriz_adj(grafo* grafo){
	int x = grafo->qtd_vertices;
	int i, j;
	printf("  ");
	for(i=0; i < x; i++){
		if (i == 0){
			for(int n = 0; n < x; n++){
				printf("%d ", n);

			}
		printf("\n");
		}
		for(j=0; j < x; j++){
			if(j == 0){
				printf("%d ", i);
			}
			printf("%d ", grafo->matriz_adjacencia[i][j]);
		}
		printf("\n");
	}
}
