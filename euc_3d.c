#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Calcular  a distancia entre dois pontos 3d
float calc_dist3(int x1, int x2, int y1, int y2, int z1, int z2){
		return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

double** criar_matriz3(int** coordenadas, int dim){
		int i, j;
		
		double** matriz = (double**) calloc(dim, sizeof(double*));
		if(!matriz){
			printf("Erro alocação.\n");
			return NULL;
		}
		
		for(i = 0; i < dim; i++){
			matriz[i] = (double*) calloc(dim, sizeof(double));
			if(!matriz[i]){
				printf("Erro alocação.\n");
				return NULL;
			}
			for(j = 0; j < dim; j++){
				matriz[i][j] = calc_dist3(coordenadas[i][1], coordenadas[j][1], coordenadas[i][2], coordenadas[j][2],coordenadas[i][3], coordenadas[j][3] );
			}
		}
	return matriz;	
}

int coord_3d(FILE** pfile, int dim){
	int i;
	Lista* L = NULL;
	int** coordenadas = NULL;
	double** matriz;
	
	coordenadas = (int**) calloc(dim, sizeof(int*));
	if(!coordenadas){
			printf("Erro alocação\n");
			return -1;
	}
	
	while(i < dim){
		coordenadas[i] = NULL;
		coordenadas[i] = (int*) calloc(4, sizeof(int));
		if(!coordenadas[i]){
			printf("Erro alocação\n");
			return -2;
		}
		if(fscanf(*pfile, "%d %d %d %d", &coordenadas[i][0], &coordenadas[i][1], &coordenadas[i][2], &coordenadas[i][3]) != 4){
			printf("Erro na leitura.");
			return -3;	
		}		
		i++;
	}
	
	matriz = criar_matriz3(coordenadas, dim);
	
	L = menor_caminho(L, dim, matriz);
	imprimir(L);
	printf("Menor distancia: %.2lf\n", distancia(L));
	
	return 0;
}
