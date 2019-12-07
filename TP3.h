#ifndef tp3_H
#define tp3_H

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "tempo.h"

int get_parametros(char **entrada, char** saida, int argc, char **argv);
int executar(int argc, char** argv, char** saida);

int existe_v(int vertice, int* conjunto);
int verificar_adj(int v, int* solution, grafo* grafo);
void ponderar(grafo* grafo);
void esvaziar_vet(int* vetor, int tamanho);
void reduzir_matriz(int** matriz, grafo* grafo);
void ordenar(int* vetor, int tamanho);
int** aloca_matriz(int n);
int pseudo_cor(int* peso, int cores);

int otimo(grafo* grafo);
int solve(int *s, int* p, int t, int** adjacentes, int valor);
void add_em_s(int* s, int* p, int t);
void remove_v(int* s, int v, int t);

int heuristica1(grafo* grafo);
int heuristica2(grafo* grafo);
void mostrar_vetor(int* v, int tamanho);
void mostrar_matriz_adj(grafo* grafo);

#endif