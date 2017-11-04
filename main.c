#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tsp.c"
#include "euc_2d.c"
#include "euc_3d.c"
#include "explicit.c"



char leitura[100]; 	//Tirar a global

char* lerLinha(FILE** pfile){
	fscanf(*pfile, "%[^\n]s", leitura);
	fgetc(*pfile);
	return leitura;
}

void tstString(FILE** pfile, char* str, char* info){ 	//Não passar o stream
	int i, j;
	//Compara se a palavra passada esta presente na linha do arquivo
	if(!strncmp(info, lerLinha(pfile), strlen(info))){
		//Caso encontre, 
		i = strlen(info);	j = 0;
		while(leitura[i] == ' ' || leitura[i] == '\t' || leitura[i] == ':')	i++;
		//Avança a linha na linha até não encontrar mais tabs, espaços ou :
		while(leitura[i] != '\n' && leitura[i] != '\0'){
			//Percorre a linha até o final, salvando o que esta escrito no vetor Str
			str[j] = leitura[i];
			i++; j++;
		}
		if(str[j] != '/')
			j++;
		str[j] = '\0';
		//Seta o final do vetor
	}

}

void tstInt(FILE** pfile, int* num, char* info){ 	//Não passar o stream
	int i;
	if(!strncmp(info, lerLinha(pfile), strlen(info))){
		i = strlen(info);	*num = 0;
		while(leitura[i] == ' ' || leitura[i] == '\t' || leitura[i] == ':')	i++;

		while(leitura[i] != '\n' && leitura[i] != '\0'){
			*num *= 10;
			*num += leitura[i] - 48;
			i++;
		}
	}

}


int main(int argc, char* argv[]){
	clock_t time_start = clock();
	//Inicia o clock para contagem do tempo

	//Cria um objeto do tipo do arquivo e variaveis para salvar os dados
	FILE * pfile;
	char nome[20];
	char type[10];
	char comment[100];
	char formato[10];
	char explicita[30];
	int dim = 0;
	
	//Set nescessário para o random
	srand((unsigned) time(NULL));	
	
	//Erro caso o arquivo não seja passada
	if(argc == 1){
		printf("Erro: Nenhum argumento passado.\n");
		return -1;
	}

	//Abre o arquivo que foi passado como parametro para main
	pfile = fopen(argv[1], "r");
	if(!pfile){	
		printf("Erro no carregamento do arquivo\n");
		return -1;	
	}

	//zera as strings
	strcpy(nome, "");
	strcpy(type, "");
	strcpy(comment, "");
	strcpy(formato, "");
	strcpy(explicita, "");

	//compara se as strings estão vazias
	//E enquantos estiverem vazias, chama a função tstString
	while(!strcmp(nome, ""))			tstString(&pfile, nome, "NAME");
	rewind(pfile);
	while(!strcmp(type, ""))			tstString(&pfile, type, "TYPE");
	rewind(pfile);
	while(!strcmp(comment, ""))		tstString(&pfile, comment, "COMMENT");
	rewind(pfile);
	while(!dim)										tstInt(&pfile, &dim, "DIMENSION");
	rewind(pfile);
	while(!strcmp(formato, ""))		tstString(&pfile, formato, "EDGE_WEIGHT_TYPE");
	rewind(pfile);
	if(!strcmp(formato, "EXPLICIT")){
			while(!strcmp(explicita, ""))		tstString(&pfile, explicita, "EDGE_WEIGHT_FORMAT");
	}

	while(strcmp(leitura, "NODE_COORD_SECTION") && strcmp(leitura, "EDGE_WEIGHT_SECTION"))	 lerLinha(&pfile);
	//Não achei nenhum arquivo que tenha "EDGE_WEIGHT_SECTION"

	printf("\nNome: %s\nTipo: %s\nComentario: %s\nDimensao: %d\nFormato: %s\n\n", nome, type, comment, dim, formato);

	printf("Lendo banco de dados...\n");
	//Compara o tipo de banco de dados
	if(!strncmp(formato, "EUC_2D", 6)){
		if(coord_2d(&pfile, dim))
		//arquivo euc_2d.c
			printf("\nERROOR!\n");
			
	}else if(!strncmp(formato, "EUC_3D", 6)){
				
		if(coord_3d(&pfile, dim))
			printf("\nERROOR!\n");
	
	}else if(!strncmp(formato, "EXPLICIT", 8)){
		printf("%s\n", explicita);
		
		if(!strncmp(explicita, "UPPER_ROW", 9)){
			if(matriz_inv(&pfile, dim))
				printf("ERROR\n");
		}		
		else if(!strncmp(explicita, "FULL_MATRIX", 11)){
			if(matriz_ex(&pfile, dim))
				printf("\nERROOR!\n");
		}
		else
			printf("Formato de matriz n suportado.\n");
	}


	printf("\n\nExecucao: %.5f s\n", (double)(clock() - time_start) / (double)CLOCKS_PER_SEC);
	return 0;
}
