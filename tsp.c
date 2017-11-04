#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define NUM_CAMIN 100

typedef struct lista{
		int cidade;
		double dist;
		struct lista* prox;
		
}Lista;

int aleatorio(int dim){
		return rand() % dim;
}
//========================================================
float distancia(Lista* L){
	Lista* aux = L;
	float soma = 0.0; 
	if(!L){
		return soma;
	}
	aux = aux->prox;
	soma += aux->dist;
	while(aux != L){
		aux = aux->prox;
		soma += aux->dist;
	}
	soma += L->dist;
	
	return soma;
}


//Insere os dados em uma lista circular
Lista* inserir(Lista* L, int cidade, double dist, double dist_ant){
		Lista* aux = L;
		Lista* novo = (Lista*) malloc(sizeof(Lista));
		novo->cidade = cidade;
		
		if(!aux){
			novo->dist = 0;
			novo->prox = novo;
			return novo;
		}
		while(aux->prox != L)
			aux = aux->prox;
			
		aux->prox = novo;
		novo->prox = L;
		aux->dist = dist_ant;
		novo->dist = dist;
		return L;
}
//Libera a lista 
void liberar(Lista* L){
		Lista* ant;

		if(L) {			
			Lista* aux = L->prox;
			do{
					ant = aux;
					aux = aux->prox;
					free(ant);
			}while(aux !=L);
			free(aux);
		}
}

Lista* caminho(Lista* L, int dim, double** matriz){
		int i, j, count, k;
		int menor = 1;
		int* controle = (int*) malloc(dim*sizeof(int));

		
		//ZERA VETOR DE CONTROLE
		for(count = 0; count < dim; count++)
			controle[count] = 0;
			
		k = aleatorio(dim);			//K GUARDA O INICIO DA LISTA
		i = k;
		L = inserir(L, i +1, 0, 0);
		controle[k] = 1;
				
		for(count = 1; count < dim; count++){				
				for(j = 0; j < dim; j++){
						if(i!=j && controle[j] != 1){
								if(matriz[i][j] < matriz[i][menor]){
									menor = j;
								}
						}
						
				}
			
				L = inserir(L, menor +1, matriz[k][menor], matriz[i][menor]);
				controle[menor] = 1;
				i = menor;
				
				//SETA MENOR PARA O PRIMEIRO ELEMENTO N USADO AINDA NA LISTA
				for(j = 0; menor == i; j++){
						if(controle[j] == 0)
							menor = j;
				}
				
		}
	return L;
}


Lista* menor_caminho(Lista* L, int dim, double** matriz){
	int i;
	Lista* aux;
	float menor = DBL_MAX;
	for(i = 0; i < NUM_CAMIN; i++){
		L = caminho(L, dim, matriz);
		if(distancia(L) <= menor){
			menor=distancia(L);
			aux=L;
		}
		L=NULL;
	}
	
	return aux;
}

void imprimir(Lista* L){
	Lista* aux = L;
	int i = 0;
	if(!L){
		printf("Lista vazia.\n");
		return;
	}
	printf("%d", aux->cidade);
	aux = aux->prox;
	i++;
	while(aux != L){
		printf(" -> %d", aux->cidade);
		i++;
		aux = aux->prox;
	}
printf("\n\nTam final: %d\n", i);
}

