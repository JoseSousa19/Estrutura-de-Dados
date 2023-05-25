#include "cliente.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>


cliente* InserirCliente (cliente* inicioC, int ID, char Nome[], char Morada[], int NIF, int Saldo, char Pass[]){ //Função para adicionar novos clientes
	
	cliente* novo = malloc(sizeof(struct Cliente)); //cria um ponteiro novo para uma estrutura Gestor alocada dinamicamente na memória.
	if (novo != NULL){
		
			novo->ID=ID; //id do cliente
			strcpy(novo->Nome,Nome); //nome do cliente
			strcpy(novo->Morada,Morada); //morada do cliente
			novo->NIF=NIF; //Nif do cliente
			novo->Saldo=Saldo; //saldo do cliente
			strcpy(novo->Pass,Pass); //pass do cliente
			novo->seguinte=inicioC;
		}
	return(novo); //retorna o novo ponteiro
}
	
	//////////////////////////////////////////////////////////////
	
cliente* AdicionarCliente(cliente* inicioC){ //Função para Adicionar um novo Cliente
	
	int ID,NIF,Saldo,inserirnovo=0;
	char Nome[20];
	char Morada[20];
	char Pass[20];
	cliente* final; 
	cliente* auxC=inicioC;
    printf("ID: \n");
    scanf("%d", &ID); // Adicionar novo ID na struct
    setbuf(stdin, NULL);

	while (inicioC != NULL){
		
       	if(inicioC->ID==ID){ //Verifica se já existe esse ID
       		
       		printf("ID ja existe\n");
       		Sleep(1000);
       		inserirnovo=1;
		}	
		inicioC=inicioC->seguinte;		
	}				
    final=auxC;
    inicioC=auxC;
    if(inserirnovo==0){
    	
    	printf("Nome: \n");
    	scanf("%[^\n]s", Nome); // Adicionar novo Nome 
    	setbuf(stdin, NULL);
       
    	printf("Morada: \n");
    	scanf("%[^\n]s", Morada); // Adicionar nova Morada 
    
     	printf("NIF: \n");
    	scanf("%d", &NIF); // Adicionar novo NIF
    
     	printf("Saldo: \n");
    	scanf("%d", &Saldo); // Adicionar novo Saldo
    	setbuf(stdin, NULL);
    
    	printf("Pass: \n");
    	scanf("%[^\n]s", &Pass); // Adicionar nova PASS
    
    	final=InserirCliente (inicioC, ID, Nome, Morada, NIF, Saldo, Pass); // Adiciona os dados à estrutura de cliente
    }
    return(final); //retorna o novo ponteiro
}
   
    ////////////////////////////////////////////////////////////// 
    
cliente* RemoverClientes(cliente* inicioC,int numero) { //Função para remover um clientes
	
	cliente *anterior=inicioC, *atual=inicioC, *aux;
 	if (atual==NULL){
 		
 		return(NULL); // lista ligada vazia
	} 
	else if (atual->ID == numero){ //Remoção do primeiro registro se o ID corresponder
	
 		aux = atual->seguinte;
  		free(atual);
  		return(aux);
 	}
 	else{
 		
 		while ((atual!=NULL)&&(atual->ID!=numero)){ //Percorrimento da lista em busca do gestor com o ID correspondente
 			
  			anterior = atual;
   			atual = atual->seguinte;
  		}
  		if (atual==NULL){ //Verificação se o gestor foi encontrado ou se chegou ao final da lista:
  			
  			return(inicioC);
		}
  		else{ // Atualização dos ponteiros para remover o gestor encontrado
  			
	  		anterior->seguinte = atual->seguinte;
   			free(atual);
   			return(inicioC);
  		}
 	}
}
	
	//////////////////////////////////////////////////////////////
	
void VisualizarClientes(cliente* inicioC){ //Função para vizualizar clientes já previamente inseridos
    
	while (inicioC != NULL){
		
       	printf("ID: %d\t"
		"Nome: %s\t"
		"Morada: %s\t\t"
		"NIF: %d\t"
		"Saldo: %d\t"
		"Pass: %s\n", inicioC->ID, inicioC->Nome, inicioC->Morada, inicioC->NIF, inicioC->Saldo, inicioC->Pass); //para cada valor inserido na estrutra a função vai ler e vai demonstrar na consola por ordem
        printf("\n");
        inicioC=inicioC->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	
void atualizarCliente(cliente* inicioC, int Acessor){ //Função para atualizar os colaboradores já inscritos
    
    while (inicioC != NULL){
    	
       	if(inicioC->ID==Acessor){ //se for o cliente pertendido vai questionar sobre os valores que são permitidos alterar
       		
       		printf("Nome: %s\n", inicioC->Nome);
       		printf("Morada: ");
    		scanf("%s", inicioC->Morada);
    		printf("NIF: %d\n", inicioC->NIF);
    		printf("Saldo: ");
    		scanf("%d", &inicioC->Saldo);
    		printf("Pass: ");
    		scanf("%s", &inicioC->Pass);
		}
		inicioC=inicioC->seguinte;
	}    
}

