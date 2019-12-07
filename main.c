#include <stdio.h>
#include <stdlib.h>
#include "TP3.h"

int main(int argc, char** argv){
	FILE* output;
	char* saida;
	int result;
	result = executar(argc, argv, &saida);
	output = fopen(saida, "w");
	fprintf(output, "%d\n", result);

return 0;	
}