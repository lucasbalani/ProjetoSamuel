#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contatos Contatos;

struct contatos{
	int PK; //Primary Key
	char nome[100];
	char telefone[30];
	char endereco[300];
	Contatos *proximo;//indica o proximo endereco de memoria
};

Contatos *primeira;
Contatos *ultima;

void adicionar(int pk, char *nome, char *telefone, char *endereco){
	Contatos *nova = (Contatos*) malloc(sizeof(Contatos));
	
	nova->PK = pk;
	strcopy(nova->nome, nome);
	strcopy(nova->telefone, telefone);
	strcopy(nova->endereco, endereco);

	nova->proximo = primeira;
	
	
	
}
void mostrarLista(){
	
	//vai guardar as informaçoes da Lista
	Contatos *auxiliar = primeira;
	
	while(auxiliar!= NULL){
		if(auxiliar->nome[0] == 'l' ){
			printf("[LISTA TELEFONICA]\n [ID %d]\nNOME - %c \nTELEFONE - %c \nENDEREÇO - %c\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
		}
	}
}
int main(int argc, char *argv[]) {
	
}
