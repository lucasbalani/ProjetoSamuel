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

//Crio duas variaveis de escopo global indicando que ser� dois espa�os do tipo Struct contatos
Contatos *primeira;
Contatos *ultima;


//fun��o que adiciona um contato na lista
void adicionar(int pk, char *nome, char *telefone, char *endereco){
	
	/*
		Aqui aloco um espa�o em memoria para guardar a struct contatos.
		
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

//Fun��o respons�vel por exibir os cadastrados na lista telefonica
void mostrarLista(char* letra){
	
	//vai guardar as informa�oes da Lista
	Contatos *auxiliar = primeira;
	
	//Valida se o campo nao est� em branco(se estiver mostrar� todos os contatos, sem o filtro)
	if (letra == "all"){
		
		//Este while percorre a lista toda
		while(auxiliar != NULL){
			printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDERE�O - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
			
			//aqui vai passar o valor do proximo endere�o para o auxiliar (Quando o proximo endere�o for null significa que � o ultimo elemento)
	 		auxiliar = auxiliar->proximo; 
		}
	} else {
		while(auxiliar != NULL){
				//este if eu testo se o primeiro caractere do nome � igual a letra passada por parametro
				if(auxiliar->nome[0] == *letra ){
					printf("[LISTA TELEFONICA]\n[ID %d]\nNOME - %s \nTELEFONE - %s \nENDERE�O - %s\n\n", auxiliar->PK, auxiliar->nome, auxiliar->telefone, auxiliar->endereco);
				}
			
			//faz a incrementa�ao passando o proximo endere�o
	 		auxiliar = auxiliar->proximo; 
		}
	}
	
}

Contatos* deletarContato(int pk){
	Contatos *atual = primeira;
	Contatos *anterior = NULL;
	
	//Testa se a lista � nula
	if (primeira == NULL){
		return NULL;
	}
	
	//Este while vai percorrer a lista ate achar o ID digitado
	while(atual->PK != pk){
		
		//checa se o proximo endere�o do ponteiro atual � igual a Nulo
		if(atual->proximo == NULL){
			return NULL;
		} else {
			
			//o no anterior passa a valer o atual
			anterior = atual;
			
			//o no atual recebe o endere�o do proximo no
			atual = atual->proximo;
		}
	}
	
	//Checa se o n� atual � igual ao primeiro n�
	if(atual == primeira){
		
		//o primeiro n� recebe o valor do proximo no
		primeira = primeira->proximo;
	}else{
		
		//o proximo n� do endere�o anterior recebe o proximo n� da atual
		anterior->proximo = atual->proximo;
	}
	
	return atual;
		
}

void cadastrarContato(){
	int pk;	
	char nome[100];
	char telefone[30];
	char endereco[300];
	
	//Leitura dos dados
	printf("Digite o ID do contato - ");
	scanf("%d", &pk);
			
	printf("\nDigite o nome do contato - ");
	scanf("%s", &nome);

	printf("\nDigite o telefone do contato - ");
	scanf("%s", &telefone);

	printf("\nDigite o endere�o do contato - ");
	scanf("%s", &endereco); 
	
	
	//adiciona na lista
	adicionar(pk, nome, telefone, endereco);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"PORTUGUESE");
	int option = 0;
	char letra[10];
	int pk;

	
	
	//Motor repeti�ao menu
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
		 	deletarContato(pk);
		 	break;
		}
		
		
		
 	}
 	
	return 0;
}
