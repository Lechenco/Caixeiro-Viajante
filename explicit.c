#include <stdio.h>
#include <stdlib.h>

//========================================================

int matriz_inv(FILE** pfile, int dim){
		int i, j;
		Lista* L = NULL;
		double** matriz = NULL;
		double** aux = NULL;
		
		matriz = (double**) calloc(dim, sizeof(double*));
		if(!matriz){
			printf("Erro alocação.\n");
			return -1;
		}
		for(i = 0; i < dim; i++){
			matriz[i] = (double*) calloc(dim, sizeof(double));
			if(!matriz[i]){
				printf("Erro alocação.\n");
				return -2;
			}
			for(j = 0; j < dim - i -1; j++){
				if(fscanf(*pfile, "%lf", &matriz[i][j]) != 1){
					printf("Erro entrada.\n");
					return -3;
				}
			}
		}
		
		aux = (double**) calloc(dim, sizeof(double*));
		if(!aux){
			printf("Erro alocação.\n");
			return -1;
		}
		for(i = 0, j = dim -1; i < dim; i++, j--){
			aux[i] = matriz[j];
		}
		
		for(i = 0; i < dim; i++){
				for(j = 0; j < dim; j++){
					if(j > i)
						aux[i][j] = aux[j][i];
				}
		}
		
		printf("Leitura Concluida\n");
		
		L = menor_caminho(L, dim, aux);
		
		imprimir(L);
		printf("Distancia percorrida: %.2lf", distancia(L));
		
		return 0;
}

int matriz_ex(FILE** pfile, int dim){
		int i, j;
		Lista* L = NULL;
		double** matriz = NULL;
		
		
		matriz = (double**) calloc(dim, sizeof(double*));
		if(!matriz){
			printf("Erro alocação.\n");
			return -1;
		}
		
		for(i = 0; i < dim; i++){
			matriz[i] = (double*) calloc(dim, sizeof(double));
			if(!matriz[i]){
				printf("Erro alocação.\n");
				return -2;
			}
			for(j = 0; j < dim; j++){
				if(fscanf(*pfile, "%lf", &matriz[i][j]) != 1){
					printf("Erro entrada.\n");
					return -3;
				}
			}
		}
		printf("Leitura Concluida\n");
		
		L = menor_caminho(L, dim, matriz);
		
		imprimir(L);
		printf("Distancia percorrida: %.2lf", distancia(L));
		
		return 0;
}
