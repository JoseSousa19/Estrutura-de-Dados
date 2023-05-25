#include "Gestor.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>

	
gestor* InserirGestor (gestor* inicio, int ID, char Nome[], char Morada[], char Pass[]){ //adicionar novos gestores

	gestor* novo = malloc(sizeof(struct Gestor)); //cria um ponteiro novo para uma estrutura Gestor alocada dinamicamente na memória.
	if (novo != NULL){
		
		novo->ID=ID; //id do gestor
		strcpy(novo->Nome,Nome); //nome do gestor
		strcpy(novo->Morada,Morada); //morada do gestor
		strcpy(novo->Pass,Pass); //palavra pass do gestor
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////	
    
gestor* AdicionarGestor(gestor* inicioG){ //Função para Adicionar um novo Gestor
	
	int ID, inserirnovo=0;
	char Nome[20];
	char Morada[20];
	char Pass[20];
	gestor* final;
	gestor* auxG=inicioG;
    printf("ID: \n");
    scanf("%d", &ID); // Adicionar novo ID na struct
    setbuf(stdin, NULL);
    
	while (inicioG != NULL){
		
       	if(inicioG->ID==ID){ //Verifica se já existe esse ID
       		
       		printf("ID ja existe\n");
       		Sleep(1000);
       		inserirnovo=1;
		}	
		inicioG=inicioG->seguinte;		
	}		
    final=auxG;
    inicioG=auxG;
    if(inserirnovo==0){ //se nao existir pede os novos dados
    	
    	printf("Nome: \n");
    	scanf("%[^\n]s", Nome); // Adicionar novo Nome
    	setbuf(stdin, NULL);
    
    	printf("Morada: \n");
    	scanf("%[^\n]s", Morada); // Adicionar nova Morada
    	setbuf(stdin, NULL);
    
    	printf("Pass: \n");
    	scanf("%[^\n]s", &Pass); // Adicionar novo ID 
    
    	final=InserirGestor (inicioG, ID, Nome, Morada, Pass);	// Adiciona os dados à estrutura de gestor
	}
	return (final); //retorna o novo ponteiro
}
   
    //////////////////////////////////////////////////////////////    
	
gestor* RemoverGestor(gestor* inicioG){ //função para remover um gestor escolhido
	
	int numero = 0;
	printf("Introduza o ID do Gestor a ser eliminado: ");
	scanf("%d", &numero);
	gestor *anterior=inicioG, *atual=inicioG, *aux;
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
  			
  			return(inicioG);
		}
  		else{ // Atualização dos ponteiros para remover o gestor encontrado
  			
	  		anterior->seguinte = atual->seguinte;
   			free(atual);
   			return(inicioG);
  		}
 	}
}
	
	//////////////////////////////////////////////////////////////
	
void VisualizarGestor(gestor* inicioG){ //Função para vizualizar gestores já previamente inseridos
   
    while (inicioG != NULL){
    	
       	printf("ID: %d\t"
		"Nome: %s\t"
		"Morada: %s\t"
		"Pass: %s\n", inicioG->ID, inicioG->Nome, inicioG->Morada, inicioG->Pass); //para cada valor inserido na estrutra a função vai ler e vai demonstrar na consola por ordem
        printf("\n");
        inicioG=inicioG->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
		
void atualizarGestor(gestor* inicioG, int Acessor){ //Função para atualizar os gestores já inscritos
  
   	while (inicioG != NULL){
   		
       	if(inicioG->ID==Acessor){ //se for o gestor pertendido vai questionar sobre os valores que são permitidos alterar
       		
			printf("Nome: %s\n", inicioG->Nome);
			printf("Morada: ");
    		scanf("%s", inicioG->Morada);
   			printf("Pass: ");
   			scanf("%s", &inicioG->Pass);
   		}
   		inicioG=inicioG->seguinte;
	}
}

