#include "mme.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>
#include "cliente.h"
#include "Gestor.h"

mme* InserirMME (mme* inicio, int ID, char Marca[], char Modelo[], int Autonomia, char Localizacao[], int Custo, int vertice){ //Função para adicionar novos MME

	mme* novo = malloc(sizeof(struct MME)); //cria um ponteiro novo para uma estrutura MME alocada dinamicamente na memória.
	if (novo != NULL){
		
		novo->ID=ID; //id do MME
		strcpy(novo->Marca,Marca); //marca do MME
		strcpy(novo->Modelo,Modelo); //modelo do MME
		novo->Autonomia=Autonomia; //autonomia do MME
		strcpy(novo->Localizacao,Localizacao); //localização do MME
		novo->Custo=Custo; //custo do MME
		novo->vertice=vertice; //vertice do MME
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////
	
aluguer* InserirAluguer (aluguer* inicio, int IDcliente, int IDmme, int Aativo){ //adicionar novos alugueres

	aluguer* novo = malloc(sizeof(struct Aluguer)); //cria um ponteiro novo para uma estrutura Aluguer alocada dinamicamente na memória.
	if (novo != NULL){
		
		novo->IDcliente=IDcliente; //id do cliente
		novo->IDmme=IDmme; //id do MME
		novo->Aativo=Aativo; //estado aluguer
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////
	
int VerticeCorrespondente (char palavra[40]){ //Função para verificar o vertice correspondente a localização
	
	char aux[40];
	char parte1[20];
    char parte2[20];
	int vertice=0;
	strcpy(aux,palavra);
	//Separação das duas primeiras palavras da variável auxiliar
    char* token = strtok(aux, "."); 
    if (token != NULL) {
    	
        strcpy(parte1, token);
        token = strtok(NULL, ".");
    }

    if (token != NULL) {
    	
        strcpy(parte2, token);
        token = strtok(NULL, ".");
    }
    //Comparação das partes com os nomes correspondentes e atribuição do número de vértice correspondente
    if (strcmp(parte1, "porto") == 0) {
    		
    	if (strcmp(parte2, "gaia") == 0){

			vertice=1;
		}
		if (strcmp(parte2, "foz") == 0){
			
    		vertice=2;
		}
		if (strcmp(parte2, "ribeira") == 0){
			
    		vertice=3;
		}
	}
	
	if (strcmp(parte1, "braga") == 0) {
		
    	if (strcmp(parte2, "maximinios") == 0){
    		
    		vertice=4;
		}
		if (strcmp(parte2, "famalicao") == 0){
			
    		vertice=5;
		}
		if (strcmp(parte2, "guimaraes") == 0){
				
    		vertice=6;
		}
	}
	if (strcmp(parte1, "barcelos") == 0) {
		
    		if (strcmp(parte2, "barcelinhos") == 0){
    			
    		vertice=7;
		}
		if (strcmp(parte2, "viatodos") == 0){
			
    		vertice=8;
		}
		if (strcmp(parte2, "negreiros") == 0){
				
    		vertice=9;
		}
	}
	return(vertice); //Retorno do número de vértice correspondente
}

	//////////////////////////////////////////////////////////////

char* AdicionarLocalizacaoNova (){ //Função para inserir localização do MME corretamente
	
	char pri[20], sec[20], ter[20] ;
	char Localizacao[40];
	printf("Cidade: \n"
			"(A)- Porto \n"
			"(B)- Braga \n"
			"(C)- Barcelos \n");
		
	char opcao;
	printf("\nOpcao escolhida: "); //Escolhe a primeira palavra do conjunto de tres que simboliza a cidade
	scanf("%c", &opcao);
	setbuf(stdin, NULL); 
	switch (opcao){
		
        case 'A':
        	strcpy(pri,"porto");
            printf("Municipio: \n"
			    "(A)- Gaia \n"
			    "(B)- Foz \n"
			    "(C)- Ribeira \n");
			printf("\nOpcao escolhida: "); //Escolhe a segunda palavra do conjunto de tres que simboliza a aldeia
			scanf("%c", &opcao);
			setbuf(stdin, NULL); 
			switch (opcao){
			    	
        		case 'A':
        			strcpy(sec,"gaia");
                	printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
					scanf("%s", &ter);
					setbuf(stdin, NULL);
				break;
						
				case 'B':
        			strcpy(sec,"foz");
                	printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
					scanf("%s", &ter);
					setbuf(stdin, NULL);
				break;
						
				case 'C':
        			strcpy("ribeira",sec);
                	printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
					scanf("%s", &ter);
					setbuf(stdin, NULL);
					break;
				}
			break;
				
				case 'B':
        			strcpy(pri,"braga");
                	printf("Municipio: \n"
			   			"(A)- Maximinos \n"
			            "(B)- Famalicao \n"
			            "(C)- Guimaraes \n");
			    	printf("\nOpcao escolhida: "); //Escolhe a segunda palavra do conjunto de tres que simboliza a aldeia
					scanf("%c", &opcao);
					setbuf(stdin, NULL);
			        switch (opcao){
			        	
        				case 'A':
        					strcpy(sec,"maximinos");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
						
						case 'B':
        					strcpy(sec,"famalicao");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
						
						case 'C':
        					strcpy(sec,"guimaraes");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
					}
				break;
				
				case 'C':
        			strcpy(pri,"barcelos");
                	printf("Municipio: \n"
			   			"(A)- Barcelinhos \n"
			            "(B)- Viatodos \n"
			            "(C)- Negreiros \n");
			    	printf("\nOpcao escolhida: "); //Escolhe a segunda palavra do conjunto de tres que simboliza a aldeia
					scanf("%c", &opcao);
					setbuf(stdin, NULL);
			        switch (opcao){
			        	
        				case 'A':
        					strcpy(sec,"barcelinhos");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
						
						case 'B':
        					strcpy(sec,"viatodos");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
						
						case 'C':
        					strcpy(sec,"negreiros");
                			printf("Localizacao: \n"); //Escolhe a terceira palavra do conjunto de tres que simboliza a rua
							scanf("%s", &ter);
							setbuf(stdin, NULL);
						break;
					}
				break;
			}
	strcpy(Localizacao, pri); 
	strcat(Localizacao, ".");
	strcat(Localizacao, sec);
	strcat(Localizacao, ".");
	strcat(Localizacao, ter); //junta as tres variaveis por ordem numa só sepradas por pontos							
   	setbuf(stdin, NULL);    
	return Localizacao; //retorna a localização completa
}

	//////////////////////////////////////////////////////////////
	
mme* AdicionarMME(mme* inicioM){ //Função para Adicionar novos Meios de Mobilidade Eletrica
	
	int ID, Autonomia, Custo, inserirnovo=0, vertice=0;
	char Marca[20];
	char Modelo[20];
	char Localizacao[40];
	mme* final;
	mme* auxM=inicioM;
	
    printf("ID: \n");
    scanf("%d", &ID); // Adicionar novo ID na struct
    
    while (inicioM != NULL){
    	
       	if(inicioM->ID==ID){ //Verifica se já existe esse ID
       		
       		printf("ID ja existe\n");
       		Sleep(1000);
       		inserirnovo=1;
		}	
		inicioM=inicioM->seguinte;		
	}		
    final=auxM;
    inicioM=auxM;
    if(inserirnovo==0){
    	
    	printf("Marca: \n");
    	scanf("%s", Marca); // Adicionar novo Marca
    	setbuf(stdin, NULL);
    
    	printf("Modelo: \n");
    	scanf("%s", Modelo); // Adicionar nova Modelo
    	setbuf(stdin, NULL);
    
    	printf("Autonomia: \n");
    	scanf("%d", &Autonomia); // Adicionar novo Autonomia
    	setbuf(stdin, NULL);  

    	strcpy(Localizacao,AdicionarLocalizacaoNova ());  // Adicionar novo localização
    	vertice = VerticeCorrespondente(Localizacao); // Adicionar novo vertice
    	printf("Custo: \n");
    	scanf("%d", &Custo); // Adicionar novo custo
    	final=InserirMME (inicioM, ID, Marca, Modelo, Autonomia, Localizacao, Custo, vertice); // Adiciona os dados à estrutura de gestor
	}
    return (final); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////
	
aluguer* AlugarMME(int Acessor, mme* inicioM, aluguer* inicioA, cliente* inicioC){ //Função de Adicionar um novo aluguer
	
	aluguer* memoA;
	aluguer* aux;
	aux=inicioA;
	memoA=inicioA;
	mme* auxM;
	auxM=inicioM;
	int ID, reservado=0, estado=1;
	char local[40];
	while(reservado!=1){
	
		reservado=0;
		printf("ID do Meio de Mobilidade Eletrica: ");
    	scanf("%d", &ID); 
    	while (inicioM != NULL){ 
    
        	if (inicioM->ID==ID){
        	
        		while (inicioA != NULL){
        		
        			if (inicioA->Aativo ==1 && inicioA->IDmme==ID){ //verifica se já não existe nenhum aluguer para aquele veiculo
        			
        				reservado=2;
        			}
        			inicioA=inicioA->seguinte; // verifica nos outros alugueres
        		}
				if (reservado=2){ //se não existir nenhum aluguer para aquele veiculo
				
					while (inicioC != NULL){ 
				
        				if (inicioC->ID==Acessor){
        				
        					if(0<=inicioC->Saldo - inicioM->Custo){ //verifica se tem saldo para alugar o MME
        					
        						inicioC->Saldo=inicioC->Saldo - inicioM->Custo; //Retirar dinheiro
        						memoA=InserirAluguer (aux, Acessor, ID, estado); // Adiciona os dados à estrutura de aluguer
        						printf("Aluguer realizado com sucesso\n");
        					}
        					else{ //caso contrario avisa que nao tem dinheiro
        					
        						printf("Nao tem dinheiro suficiente, por favor, carregue o saldo\n");
							}
        				}
        				inicioC=inicioC->seguinte; // verifica nos outros clientes
      				}
        			reservado=1; //faz reset a variavel
        			system("PAUSE");
				}
			}
		inicioM=inicioM->seguinte;	// verifica nos outros MMEs
		}
		if (reservado!=1){	
	
			system("cls");
    		printf("ID do Meio de Mobilidade Eletrica Nao Existe ou Ja Alugado");
    		Sleep(1000);
    		system("cls");
    		inicioM=auxM;
		}
	}
	return(memoA); //retorna o novo ponteiro
}
	
	//////////////////////////////////////////////////////////////
	
mme* RemoverMME(mme* inicioM) { //Função para remover um MME
	
	int numero = 0;
	printf("Introduza o ID do Meio de Mobilidade Eletrico a ser eliminado: ");
	scanf("%d", &numero);
	mme *anterior=inicioM, *atual=inicioM, *aux;

 	if (atual==NULL){
 		
 		return(NULL); // lista ligada vazia
	 } 
	else if (atual->ID == numero){ // //Remoção do primeiro registro se o ID corresponder
	
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
  			
  			return(inicioM);
		}
  		else{ // Atualização dos ponteiros para remover o gestor encontrado
  			
	  		anterior->seguinte = atual->seguinte;
   			free(atual);
   			return(inicioM);
  		}
 	}
}

	//////////////////////////////////////////////////////////////
	
void VisualizarMME(mme* inicioM){ //Função para vizualizar MMEs já previamente inseridos

   while (inicioM != NULL){
   	
       	printf("ID: %d\t"
		"Marca: %s\t"
		"Modelo: %s\t"
		"Autonomia: %d\t"
		"Localizacao: %s\t\t"
		"Custo: %d\t", inicioM->ID, inicioM->Marca, inicioM->Modelo, inicioM->Autonomia, inicioM->Localizacao, inicioM->Custo); //para cada valor inserido na estrutra a função vai ler e vai demonstrar na consola por ordem
        printf("\n");
        inicioM=inicioM->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	
void atualizarMME(mme* inicioM){ //Função para atualizar os colaboradores já inscritos
  
  	int numero=0;
	printf("Introduza o ID do Meio de Mobilidade Eletrica a ser atualizado: ");
	scanf("%d", &numero);
	while (inicioM != NULL){
		
       	if(inicioM->ID==numero){ //se for o MME pertendido vai questionar sobre os valores que são permitidos alterar
       		
			printf("Marca: %s\n", inicioM->Marca);
			printf("Modelo: %s\n", inicioM->Modelo);
			printf("Autonomia: ");
    		scanf("%d", &inicioM->Autonomia);
    		setbuf(stdin, NULL);
    		strcpy(inicioM->Localizacao,AdicionarLocalizacaoNova ());
    		inicioM->vertice = VerticeCorrespondente(inicioM->Localizacao);
    		printf("Custo: ");
    		scanf("%d", &inicioM->Custo);
		}
		inicioM=inicioM->seguinte;
	}
}    

	//////////////////////////////////////////////////////////////
	
void HistoricoAluguerMME(aluguer* inicioA ,mme* inicioM, cliente* inicioC){ //Função para verificar os historicos de aluguer de MME
	
	cliente* auxC=inicioC;
	mme* auxM=inicioM;
	char estado[20];
	while (inicioA != NULL){
		
		inicioC=auxC;
		while (inicioC != NULL){
			
			if(inicioA->IDcliente==inicioC->ID){ //se o ID guardado do cliente no aluguer correponder ao id do cliente analisado na estrutura de clientes
				
				printf("ID: %d\t"
				"Nome: %s\t"
				"Morada: %s\t"
				"NIF: %d\t\t"
				"Saldo: %d\t"
				"Pass: %d\n", inicioC->ID, inicioC->Nome, inicioC->Morada, inicioC->NIF, inicioC->Saldo, inicioC->Pass); //para cada valor inserido na estrutra a função vai ler e vai demonstrar na consola por ordem
        		printf("\n");
			}
			inicioC=inicioC->seguinte;
		}
		inicioM=auxM;
		while (inicioM != NULL){
			
			if(inicioA->IDmme==inicioM->ID){  //se o ID guardado do MME no aluguer correponder ao id do MME analisado na estrutura de clientes
				
				printf("ID: %d\t"
				"Marca: %s\t"
				"Modelo: %s\t"
				"Autonomia: %d\t"
				"Localizacao: %s\t\t"
				"Custo: %d\t", inicioM->ID, inicioM->Marca, inicioM->Modelo, inicioM->Autonomia, inicioM->Localizacao, inicioM->Custo); //para cada valor inserido na estrutra a função vai ler e vai demonstrar na consola por ordem
        		printf("\n");
			}
			inicioM=inicioM->seguinte;
		}
		if(inicioA->Aativo==1){ //verifica se a varialvel esta a 0 ou 1 para corresponder os printf
			
			strcpy(estado, "Ativo");
		}
		else{
			
			strcpy(estado, "Desativo");
		}
	printf("\nEstado: (%s)\n",estado);
	printf("========================================================================================================================\n\n");
	inicioA=inicioA->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	
void PercentagemMMEAlugados(aluguer* inicioA ,mme* inicioM){ //Função para determinar a percentagem de MME alugados
	
	int contagem=0,percentagem=0,totalM=0;
	while (inicioA != NULL){
		
		if(inicioA->Aativo==1){ //se o aluger estiver ativo
			
			contagem ++; //incrementa 1
		}
		inicioA=inicioA->seguinte;
	}
	while (inicioM != NULL){
		
		totalM++; //conta quantos MMEs existem na estrutura
		inicioM=inicioM->seguinte;
	}
	percentagem=contagem*100/totalM; //converte para media de alugueres
	printf("A Percentagem de Meios de Mobilidade Eletrica Alugados e: %d\n", percentagem);
}

	//////////////////////////////////////////////////////////////

void AtualizarEstadoAluguer(aluguer* inicioA, int Acessor,mme* inicioM ) { //Função para terminar aluguer
	
	int aux=0;
	while (inicioA != NULL){
		
		if (Acessor==inicioA->IDcliente && inicioA->Aativo==1){ //se o aluguer em analise correponder ao solicitado
			
			inicioA->Aativo=0;
			aux=1;
			while(inicioM != NULL){
				
				if(inicioM->ID == inicioA->IDmme){ //se o MME em analise corresponder ao alugado vai pedir para alterar alguns dados
					
					printf("\nAutonomia do Meio de Mobilidade Eletrica:\n"); //pede nova autonomia
					scanf("%d", &inicioM->Autonomia);
					printf("\nLocalizacao atual do Meio de Mobilidade Eletrica"); //pede nova localização que envolve novo vertice atraves das funcoes vistas acima
					setbuf(stdin, NULL);
					Sleep(500);
					strcpy(inicioM->Localizacao , AdicionarLocalizacaoNova ());
    				inicioM->vertice = VerticeCorrespondente(inicioM->Localizacao);
    				system("cls");
    				printf("Correcao\n"); //demonstra os novos dados
    				printf("\nAutonomia:\n%d\n",inicioM->Autonomia);
    				printf("\nLocalizacao atual do Meio de Mobilidade Eletrica:\n%s\n",inicioM->Localizacao);
    				printf("\nVertice:\n%d\n\n",inicioM->vertice);
    				system("PAUSE");
				}
				inicioM=inicioM->seguinte;
			}
			printf("Terminado com Sucesso");
		}
		inicioA=inicioA->seguinte;
	}
	if (aux==0){ //se nao encontrar nenhum aluguer associado aquele ID de cliente
		
		printf("Nenhum Aluguer Correspondente Encontrado");
		Sleep(1000);
	}	
}

	//////////////////////////////////////////////////////////////
	
void DecrescenteAutonomia(mme* inicioM) { //Função para determinar a ordem decrescente de autonomia
	
	mme *mme1 = inicioM; // Ponteiro para percorrer a lista
	mme *inicio; // Ponteiro para guardar o início da lista
	
	while (mme1 != NULL){
		
    	mme *mme2 = mme1->seguinte; // Ponteiro para comparar com mme1
    	inicio = mme2; // Guarda o início da lista para percorrer novamente
    	while (mme2 != NULL){
    		
        	if (mme1->Autonomia < mme2->Autonomia){ // Se a autonomia for maior, troca o conteúdo dos nós
        	
            	int temp = mme1->Autonomia; // Variável temporária para trocar a autonomia
            	char aux[40]; // Vetor auxiliar para trocar strings
            	mme1->Autonomia = mme2->Autonomia; // Troca dos valores de Autonomia
            	mme2->Autonomia = temp;
            	
            	strcpy(aux,mme2->Marca); // Troca dos valores de Marca
            	strcpy(mme1->Marca,mme2->Marca);
            	strcpy(mme2->Marca,aux);
            	
            	strcpy(aux,mme2->Modelo); // Troca dos valores de Modelo
            	strcpy(mme1->Modelo,mme2->Modelo);
            	strcpy(mme2->Modelo,aux);
            	
            	strcpy(aux,mme1->Localizacao); // Troca dos valores de Localizacao
            	strcpy(mme1->Localizacao,mme2->Localizacao);
            	strcpy(mme2->Localizacao,aux);
            	
				temp=mme1->Custo; // Troca dos valores de Custo
            	mme1->Custo = mme2->Custo;
            	mme2->Custo= temp;

        	}
        	mme2 = mme2->seguinte; // Avança para o próximo nó
    	}
 		mme1 = mme1->seguinte; // Avança para o próximo nó
	}
	while (inicioM != NULL){
		
       	printf("ID: %d\t" // Impressão dos valores dos nós ordenados
		"Marca: %s\t"
		"Modelo: %s\t"
		"Autonomia: %d\t"
		"Localizacao: %s\t\t"
		"Custo: %d\t", inicioM->ID, inicioM->Marca, inicioM->Modelo, inicioM->Autonomia, inicioM->Localizacao, inicioM->Custo);
        printf("\n");
        inicioM=inicioM->seguinte; // Avança para o próximo nó
	}
}

	//////////////////////////////////////////////////////////////
	
int PesquisaPorLocalizacao(mme* inicioM){ //Função os MMEs mais pertos e suas distancias
    
	int aux = 0,local=0 ;
	printf("\n\n\n Localizacao correspondente a cada ID  \n" //pede para escolher a localização aproximada do cliente
		   "|	Id	|	Localizacao             | \n"
		   "|	1	|	porto.gaia              | \n"
		   "|	2	|	porto.foz               | \n"
		   "|	3	|	porto.ribeira           | \n"
		   "|	4	|	braga.maximinos         | \n"
		   "|	5	|	braga.famalicao         | \n"
		   "|	6	|	braga.guimaraes         | \n"
		   "|	7	|	barcelos.barcelinhos    | \n"
		   "|	8	|	barcelos.viatodos       | \n"
		   "|	9	|	barcelos.negreiros      | \n");
		   
	printf("\n\nEscolha o numero relativo a sua localizacao: \n");
	scanf("%d", &local);
 	return(local); //retorna a sua localização
 	
}

	//////////////////////////////////////////////////////////////
	
void CarregarSaldo(cliente* inicioC, int Acessor){ //Função para carregar saldo do cliente
	
	int dinheiro=0;
	printf("Montante a carregar: ");
    scanf("%d", &dinheiro); //dinheiro para acrescentar ao do cliente
	while (inicioC != NULL){
		
		if(Acessor == inicioC->ID){ //verifica se o cliente é o certo
		
			inicioC->Saldo= dinheiro + inicioC->Saldo; //adiciona o dinheiro ao existente e grava na estrutura do cliente
			printf("O seu Saldo e: %d",inicioC->Saldo);
			Sleep(1000);
		}
		inicioC=inicioC->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	
void HistoricoCliente(int Acessor, mme* inicioM, aluguer* inicioA){ //Função para mostrar historico do cliente
	
	mme* auxM=inicioM;
	while (inicioA != NULL){
		
		if(inicioA->IDcliente == Acessor){ //se o ID guardado do cliente no aluguer correponder ao id do cliente analisado na estrutura de clientes
			
			inicioM=auxM;
			while (inicioM != NULL){
				
				if(inicioA->IDmme == inicioM->ID){ //se o ID guardado do MME no aluguer correponder ao id do MME analisado na estrutura de clientes
					
        			printf("ID: %d\n", inicioM->ID);
        			printf("Marca: %s\n", inicioM->Marca);
        			printf("Modelo: %s\n", inicioM->Modelo);
        			printf("Custo: %d\n", inicioM->Custo);
        			if (inicioA->Aativo==1){ //verifica se a varialvel esta a 0 ou 1 para corresponder os printf
        				
        				printf("Aluguer Ativo \n");
					}
					else{
						
						printf("Aluguer Desativo \n");
					}
        			printf("\n\n");
				}
				inicioM=inicioM->seguinte;
			}
		}
		inicioA=inicioA->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	
void MMEsemAluguer(mme* inicioM, aluguer* inicioA){ //Função para verificar os MMEs sem aluguer ativo
	
	aluguer* auxA=inicioA;
	int ID=0, aux=0;
	while (inicioM != NULL){
		
		ID=inicioM->ID;
		inicioA=auxA;
		while (inicioA != NULL){
			
			if (inicioA->IDmme==ID && inicioA->Aativo==1){ //se o id do MME for igual ao do aluguer e o aluguer estiver a ativo
				
				aux=1;
			}
			inicioA=inicioA->seguinte;
		}
		if (aux==0){
			
			printf("ID: %d\n", inicioM->ID);
        	printf("Marca: %s\n", inicioM->Marca);
        	printf("Modelo: %s\n", inicioM->Modelo);
        	printf("Autonomia: %d\n", inicioM->Autonomia);
        	printf("Localizacao: %s\n", inicioM->Localizacao);
        	printf("Custo: %d\n", inicioM->Custo);
        	printf("\n\n");	//mostra os dados do MME sem aluguer
		}
		aux=0;
		inicioM=inicioM->seguinte;
	}
}

	//////////////////////////////////////////////////////////////
	

