#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char leitura[100];

char* lerLinha(FILE** pfile){
	fscanf(*pfile, "%[^\n]s", leitura);
	fgetc(*pfile);
	return leitura;
}

void tstString(FILE** pfile, char* str, char* info){ 	//Não passar o stream
	int i, j;
	if(!strncmp(info, lerLinha(pfile), strlen(info))){
		i = strlen(info);	j = 0;
		while(leitura[i] == ' ' || leitura[i] == '\t' || leitura[i] == ':')	i++;

		while(leitura[i] != '\n' && leitura[i] != '\0'){
			str[j] = leitura[i];
			i++; j++;
		}
		if(str[j] != '/')
			j++;
		str[j] = '\0';
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
