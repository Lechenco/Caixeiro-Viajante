#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

//Calcular  a distancia entre dois pontos 2d
double calc_dist2(int x1, int x2, int y1, int y2){
		return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double** criar_matriz2(double** coordenadas, int dim){
		int i, j;
		//Cria o vetor dinamico ja zerado
		double** matriz = (double**) calloc(dim, sizeof(double*));
		if(!matriz){
			//Erro caso a alocação falhe
			printf("Erro alocação.\n");
			//~ return -1;
			//Pq tirou os returns nos erros?
		}
		
		for(i = 0; i < dim; i++){
			matriz[i] = (double*) calloc(dim, sizeof(double));
			//Como é um vetor, cria um novo vetor para cada linha do vetor anterior, fazendo assim uma matriz
			if(!matriz[i]){
				//Erro caso a alocação falhe
				printf("Erro alocação.\n");
				//~ return -2;
			}
			for(j = 0; j < dim; j++){
			
				matriz[i][j] = calc_dist2(coordenadas[i][1], coordenadas[j][1], coordenadas[i][2], coordenadas[j][2]);
				
			}
	}
	return matriz;	

}

int coord_2d(FILE** pfile, int dim){
	int i;
	Lista* L = NULL;

	double** coordenadas = NULL;
	double** matriz;
	
	coordenadas = (double**) malloc(dim* sizeof(double*));
	//Aloca as coordenadas
	if(!coordenadas){
			//Erro caso a alocação falhe
			printf("Erro alocação\n");
			return -1;
	}
	
	i = 0;
	while(i < dim){
		coordenadas[i] = NULL;
		coordenadas[i] = (double*) malloc(3* sizeof(double));
		//Cria uma matriz de coordenadas, sendo que a primeira coluna é o X, a segunda o Y e a terceira o Controle
		if(!coordenadas[i]){
			printf("Erro alocação\n");
			return -2;
		}
		if(fscanf(*pfile, "%lf %lf %lf", &coordenadas[i][0], &coordenadas[i][1], &coordenadas[i][2]) != 3){
			printf("Erro na leitura.");
			return -3;	
		}
		i++;
	}
	printf("Leitura Concluida\n\n");
	//Chama a função que cria a matriz quad
	matriz = criar_matriz2(coordenadas, dim);
	
	L = menor_caminho(L, dim, matriz);
	
	printf("CAMINHO\n");
	imprimir(L);

	printf("Distancia percorrida: %.2f\n", distancia(L));

	return 0;
}
