#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct contatos Contatos;

struct contatos{
	int PK; //Primary Key
	char nome[100];
	char telefone[30];
	char endereco[300];
	Contatos *proximo;//indica o proximo endereco de memoria
};

//Crio duas variaveis de escopo global indicando que será dois espaços do tipo Struct contatos
Contatos *primeira;
Contatos *ultima;


//função que adiciona um contato na lista
void adicionar(int pk, char *nome, char *telefone, char *endereco){
	
	/*
		Aqui aloco um espaço em memoria para guardar a struct contatos.
		
		o malloc retorna um ponteiro void, por isso precisamos do cast (Contatos*),
		para converter o ponteiro void em um ponteiro struct contatos.
	*/
	Contatos *nova = (Contatos*) malloc(sizeof(Contatos));
	//Setando os atributos da struct contatos
	nova->PK = pk;
	strcpy(nova->nome, nome);
	strcpy(nova->telefone, telefone);
	strcpy(nova->endereco, endereco);

	nova->proximo = primeira;
	
	primeira = nova;
	
	
	
}

//Função responsável por exibir os cadastrados na lista telefonica
void mostrarLista(char* letra){
	
	//vai guardar as informaçoes da Lista
	Contatos *auxiliar = primeira;
	
	//Valida se o campo nao está em branco(se estiver mostrará todos os contatos, sem o filtro)
	if (letra == "all"){
		
		//Este while percorre a lista toda
		while(auxiliar != NULL){
			printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDEREÇO - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
			
			//aqui vai passar o valor do proximo endereço para o auxiliar (Quando o proximo endereço for null significa que é o ultimo elemento)
	 		auxiliar = auxiliar->proximo; 
		}
	} else {
		while(auxiliar != NULL){
				//este if eu testo se o primeiro caractere do nome é igual a letra passada por parametro
				if(auxiliar->nome[0] == *letra ){
					printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDEREÇO - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
				}
			
			//faz a incrementaçao passando o proximo endereço
	 		auxiliar = auxiliar->proximo; 
		}
	}
	
}

Contatos* deletarContato(int pk){
	Contatos* atual = primeira;
	Contatos* anterior = NULL;
	
	//Testa se a lista é nula
	if (primeira == NULL){
		return NULL;
	}
	
	
	while(atual->PK != pk){
		if(atual->proximo == NULL){
			return NULL;
		} else {
			anterior = atual;
			atual = atual->proximo;
		}
	}
	
	if(atual == primeira){
		primeira = primeira->proximo;
	}else{
		anterior->proximo = atual->proximo;
	}
	
	return atual;
		
}

void cadastrarContato(){
	int pk;	
	char nome[100];
	char telefone[30];
	char endereco[300];
			
	printf("Digite o ID do contato - ");
	scanf("%d", &pk);
			
	printf("\nDigite o nome do contato - ");
	scanf("%s", &nome);

	printf("\nDigite o telefone do contato - ");
	scanf("%s", &telefone);

	printf("\nDigite o endereço do contato - ");
	scanf("%s", &endereco); 
	
	adicionar(pk, nome, telefone, endereco);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"PORTUGUESE");
	int option = 0;
	char letra[1];
	int pk;

	
	
	//Motor repetiçao menu
	while(option != 4){
		
		fflush(stdin);
		printf("[LISTA TELEFONICA]\n 1 - Adicionar um contato\n 2 - Mostrar contatos\n 3 - Deletar Contato\n 4 - Sair\n");
		scanf("%d", &option);
		switch(option){
		 case 1:
			cadastrarContato();
			break;
		 case 2:
		 	printf("Deseja filtrar por qual letra ? (Se quiser listar sem filtro digite - all)");
		 	scanf("%s", &letra);
		 	mostrarLista(letra);
		 	break;
		 case 3:
		 	printf("Qual o id que deseja deletar?\n");
		 	scanf("%d", pk);
		 	break;
		}
		
		
		
 	}
 	
	return 0;
}
