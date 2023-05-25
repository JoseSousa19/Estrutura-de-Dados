#include "distancias.h"
#include "mme.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>
#define INFINITY 9999

distancia* InserirDistancias (distancia* inicio, int IdOrigem, int IdDestino, int Distancia){ //adicionar novas estradas direcionais

	distancia* novo = malloc(sizeof(struct Distancia)); //cria um ponteiro novo para uma estrutura Distancia alocada dinamicamente na mem�ria.
	if (novo != NULL){
		novo->IdOrigem=IdOrigem; //vertice de origem
		novo->IdDestino=IdDestino; //vertice de destino
		novo->Distancia=Distancia; //distancia entre vertice
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////

distancia* AdicionarNovaDistancia(distancia* inicioD){ //Adicionar novas distancias
	
	int IdOrigem, IdDestino, Distancia, inserirnovo=0;
	char Localizacao[40];
	distancia* final;
	distancia* auxD=inicioD;
	
   	printf("Id Origem: \n");
   	scanf("%d", &IdOrigem); // Adicionar novo vertice de origem
    
   	printf("Id Destino: \n");
   	scanf("%d", &IdDestino); // Adicionar novo vertice de destino
   	
   	printf("Distancia: \n");
   	scanf("%d", &Distancia); // Adicionar nova distancia entre vertice
   	setbuf(stdin, NULL);

   	final=InserirDistancias (inicioD, IdOrigem, IdDestino, Distancia); // chama a fu��o de guardar novas distancias e espera receber o novo inicio
    return (final); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////

void VisualizarDistancas(distancia* inicioD){ //Vizualiza as estradas/distancias j� previamente inseridos

	printf("|    Id Origem        Id Destino        Distancia     \n");
   	while (inicioD != NULL){ 
   		
       	printf("|____________________________________________________ \n"
			   "|    %d                %d                 %d             \n"
		,inicioD->IdOrigem, inicioD->IdDestino, inicioD->Distancia); //para cada valor inserido na estrutra a fun��o vai ler e vai demonstrar na consola por ordem
        inicioD=inicioD->seguinte;
	}
	printf("\n\n\n Localizacao correspondente a cada ID  \n" //zona correspondente a cada vertice
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
}

	//////////////////////////////////////////////////////////////
	
int inserirAresta(Adjacentes Grafo[], int v1, int v2, float p){ //adicionar novas arestas ao grafo
	
	Adjacentes novo;
 	if ((v1 >= 0) && (v1 < VERTICES) && (v2 >= 0) && (v2 < VERTICES) && (p >= 0)){
 		
	 	novo = (Adjacentes) malloc(sizeof(struct registo));  // Aloca mem�ria para uma nova estrutura "registo"
  		novo->id = v2;  // Atribui o valor de v2 ao campo "id" da nova estrutura
  		novo->peso = p;  // Atribui o valor de p ao campo "peso" da nova estrutura
  		novo->seguinte = Grafo[v1];  // Atribui o valor atual de Grafo[v1] ao campo "seguinte" da nova estrutura
  		Grafo[v1] = novo;  // Atualiza Grafo[v1] para apontar para a nova estrutura
  		return(1);  // Retorna 1 para indicar que a inser��o foi bem-sucedida
 	}
 	else return(0); // Retorna 0 para indicar que a inser��o falhou devido a valores inv�lidos
}	

	//////////////////////////////////////////////////////////////

void inicializarGrafo(Adjacentes Grafo[]){ //limpa o array grafo ao iniciar
	
	int i;
 	for(i=0; i<VERTICES; i++) {
 		
 		Grafo[i] = NULL;  // Inicializa cada posi��o do array Grafo com o valor NULL
 	}
}

	//////////////////////////////////////////////////////////////

void converter(Adjacentes Grafo[], int Matriz[][VERTICES]){ //converte grafos em matrizes
	
	int i, j;
 	Adjacentes aux;
 	for(i = 0; i < VERTICES; i++) {	// Inicializa todos os elementos da matriz com o valor 0
 	
    	for(j = 0; j < VERTICES; j++) {
    		
    		Matriz[i][j] = 0;
    	}
 	}
 	for(i = 0; i < VERTICES; i++){	// Percorre o array de Grafo e preenche a matriz com os pesos das arestas
 		
	 	aux = Grafo[i];
   		while (aux != NULL){
   			
		   Matriz[i][aux->id] = aux->peso;  // Atribui o peso da aresta entre os v�rtices i e aux->id na matriz
    		aux = aux->seguinte;  // Atualiza aux para apontar para a pr�xima adjac�ncia
   		}
  	}
}

	//////////////////////////////////////////////////////////////

int dijkstra(int G[VERTICES][VERTICES],int n,int startnode,mme* inicioM,aluguer* inicioAl){ //encontrar o melhor caminho para cada vertice e a distancia at� ao mesmo
 		
	int cost[VERTICES][VERTICES],distance[VERTICES],pred[VERTICES];
	int visited[VERTICES],count,mindistance,nextnode,i,j,menordistancia=9999,verticemenor=0;
	for(i = 0; i < n; i++){ // Inicializa a matriz de custos 'cost' com base na matriz de adjac�ncias 'G'
		
		for(j = 0; j < n; j++){
			
			if(G[i][j] == 0){
			
				cost[i][j] = INFINITY;
			}
			else{
			
				cost[i][j] = G[i][j];
			}
		}
	}
	for(i = 0; i < n; i++){ // Inicializa os arrays distance, pred e visited
		
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1){
		
		mindistance=INFINITY;
		for(i = 0; i < n; i++){ // Encontra o v�rtice n�o visitado com a menor dist�ncia
			
			if(distance[i] < mindistance && !visited[i]){
				
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode]=1;// Atualiza as dist�ncias dos v�rtices vizinhos n�o visitados
		for(i = 0; i < n; i++){

			if(!visited[i]){
			
				if(mindistance+cost[nextnode][i]<distance[i]){
		
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
			}
		}
		count++;
	}
	mme* aux=inicioM;
	aluguer* auxAl=inicioAl;
	int tem=0,apoio=1,naotem=1,auxiliardistancias=9999;
	for(i=0;i<n;i++){

		if(i!=startnode){
	
 			if (distance[i]<menordistancia){  //se a distancia que precisa para chegar do local onde se encontra at� ao vertice i for menor que a menordistancia

 				while(inicioM != NULL){	

 					if (i == inicioM->vertice){ //se o vertice do meio de mobilidade for igual ao i

	 					naotem=0; //vai colocar a variavel naotem em 0 para demonstrar que existe algum meio no vertice i
	 					apoio=1;
 						while(inicioAl != NULL){
 		
 							if (inicioM->ID == inicioAl->IDmme && inicioAl->Aativo == 1 ){  //Utilizado para verificar se existe aluguer ativo para o meio de mobilidade em quest�o
 		
 								apoio=0; // se j� houver algum aluguer a variavel apoio fica a 0
 							}
 							if (inicioM->ID != inicioAl->IDmme && inicioM->vertice == i && apoio==1 && inicioAl->Aativo == 1){  //Utilizado para verificar se n�o existe aluguer ativo para o meio de mobilidade em quest�o mas os vertices sao iguais

 								apoio=1; // se j� houver algum aluguer a variavel apoio fica a 0
 							}
 							inicioAl=inicioAl->seguinte; // verifica nos outros aluguer
 						}
						inicioAl=auxAl; // volta a colocar o inicio direcionado para o primeiro aluguer 
 					}
 					inicioM=inicioM->seguinte; // verifica nos outros meios de mobilidade 
 				}
 				if (naotem == 1){ //significa que para o vertice i n�o existe nenhum meio de mobilidade
 	
 					apoio=0; // colocar a variavel de verifica��o de aluguers ativos a 0 para referenciar que n�o h� nada disponivel no vertice i
	 			}
 				naotem=1; //ao fim de correr todos os meio de mobilidade 
 				inicioM=aux; // volta a colocar o inicio direcionado para o primeiro meio de mobilidade
 				if (apoio==1){	//se existir algum meio de mobilidade e n�o existir aluguer sobre ele
 	
 					tem=1;  //coloca a varialvel tem a 1		
 				}
 				if(tem==1){ //se existir algum meio de mobilidade e n�o existir aluguer sobre ele
 		
 					auxiliardistancias=distance[i]; //guarda a distancia do ultimo vertice disponivel para se existir um vertice que n�o tem meios
 					menordistancia=distance[i]; //guarda a dist�ncia do vertice na varialvel menordistancia
 					verticemenor=i; //guarda o vertice i na variavel verticemenor
 				}
			}
			if (apoio==0){	//se n�o existir algum meio de mobilidade ou existir aluguer sobre ele 
	
 	 			menordistancia=auxiliardistancias; //volta a colocar a variavel menordistancia com um valor do ultimo vertice com meios de mobilidade			
 			}
	 		apoio=1; //ap�s completar um ciclo coloca a variavel apoio a 1
	 		tem=0;
			naotem=1;
		}
	}
	printf("\nDistancia aproximada ate ao destino %d" ,menordistancia);
	printf("\nLocais a passar=%d",verticemenor);	
	j=verticemenor;
	do{
		
		j=pred[j];
		printf("<-%d",j);
	}
	while(j!=startnode);
	printf("\n\n");
	return(verticemenor);
}

	//////////////////////////////////////////////////////////////

visitado* InserirVisitado (visitado* inicio, int IdVisitado){ //adiciona novo vertice visitado

	visitado* novo = malloc(sizeof(struct Visitado)); //cria um ponteiro novo para uma estrutura Visitado alocada dinamicamente na mem�ria.
	if (novo != NULL){
		
		novo->IdVisitado=IdVisitado; //Vertice visitado
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////

tcamiao* InserirTCamiao (tcamiao* inicio, int IdVUltimoV, int NumeroMME, int DistanciaTotal){ //adiciona novo caminho de recolha

	tcamiao* novo = malloc(sizeof(struct TCamiao));  //cria um ponteiro novo para uma estrutura TCamiao alocada dinamicamente na mem�ria.
	if (novo != NULL){
		
		novo->IdVUltimoV=IdVUltimoV; //ultimo vertice visitado
		novo->NumeroMME=NumeroMME; //numero total de MME na volta
		novo->DistanciaTotal=DistanciaTotal; //distancia total da volta
		novo->seguinte=inicio; //interliga a nova memoria com a antiga
	}
	return(novo); //retorna o novo ponteiro	
}

	//////////////////////////////////////////////////////////////
	
tcamiao* dijkstracamiao(int n, int startnode, int Nvertices, distancia* inicioD, aluguer* inicioAl, mme* inicioM, visitado* inicioV, int Retorno, tcamiao* inicioTC){ //determinar pelo metodo de dijkstra o caminho mais perto para recolha ods MMEs
 	
 	int NumeroMME=inicioTC->NumeroMME;
 	mme* auxM=inicioM;
	visitado* auxV=inicioV; visitado* Invercao=NULL; visitado* Visitados=NULL; visitado* auxVisitados=NULL; visitado* ModEstado=NULL;
	int VerticeSeguinte=0, DistanciaAtual, AuxiliarContagemVertice=0, DistanciaTotal=0, UltimoVertice=startnode,Percorridos=0;
	Visitados=InserirVisitado (Visitados, startnode); 
	auxVisitados=Visitados;
	int Matriz[VERTICES][VERTICES]; // Cria��o e preenchimento da matriz de adjac�ncia
    Adjacentes Grafo1[VERTICES];  
 	inicializarGrafo(Grafo1);
    while (inicioD != NULL)	{
    						
    	inserirAresta(Grafo1,inicioD->IdOrigem,inicioD->IdDestino,inicioD->Distancia);
    	inicioD=inicioD->seguinte;
	}
	converter(Grafo1, Matriz);
	VerticeSeguinte=startnode;
	DistanciaAtual=9999;	
	int cost[VERTICES][VERTICES],distance[VERTICES],pred[VERTICES];
	int visited[VERTICES],count,mindistance,nextnode,i,j,menordistancia=9999,verticemenor=0;
	for(i = 0; i < n; i++){ // Inicializa a matriz de custos 'cost' com base na matriz de adjac�ncias 'G'
		
		for(j = 0; j < n; j++){
			
			if(Matriz[i][j] == 0){
			
				cost[i][j] = INFINITY;
			}
			else{
			
				cost[i][j] = Matriz[i][j];
			}
		}
	}
	for(i = 0; i < n; i++){ // Inicializa os arrays distance, pred e visited
		
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1){
		
		mindistance=INFINITY;
		for(i = 0; i < n; i++){ // Encontra o v�rtice n�o visitado com a menor dist�ncia
			
			if(distance[i] < mindistance && !visited[i]){
				
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode]=1;// Atualiza as dist�ncias dos v�rtices vizinhos n�o visitados
		for(i = 0; i < n; i++){

			if(!visited[i]){
			
				if(mindistance+cost[nextnode][i]<distance[i]){
		
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
			}
		}
		count++;
	}
	if(Retorno != 0){ //se j� acabaram os MME para recolha ou ja atingiu o limite por volta

		for(i=0;i<n;i++){
		
			if(i!=startnode){ // Verifica se i � diferente do n� de partida

 				if (i == Retorno){  //se a distancia que precisa para chegar do local onde se encontra at� ao vertice i for menor que a menordistancia

 					menordistancia=distance[i]; //guarda a dist�ncia do vertice na varialvel menordistancia
 					verticemenor=i; // Guarda o v�rtice com a menor dist�ncia
				}
			}
		}
		inicioTC=InserirTCamiao (inicioTC, verticemenor, NumeroMME, menordistancia); // Insere os dados para contabilizar o limite de MME distancias a percorrer e vertice que ficou
		j=verticemenor; // Atribui o valor do v�rtice com a menor dist�ncia � vari�vel j
		do{
		
			j=pred[j]; // Atribui o valor de pred[j] a j
			if(startnode != j ){ // Verifica se o n� de partida � diferente de j
				
				Invercao=InserirVisitado (Invercao, j); // Insere informa��es para proceder a invers�o de dados dentro da estrutura
			}
		}while(j!=startnode); // O loop continua enquanto j n�o � igual ao n� de partida
		while(Invercao != NULL){
					
			printf("Proximo Vertice:  %d\n",Invercao->IdVisitado);  // Imprime o pr�ximo v�rtice visitado
			printf("\n========================================================================================================================================\n\n");
			Invercao=Invercao->seguinte; // verifica nos outros meios de mobilidade 
		}
		Invercao=NULL; // Reinicia a vari�vel Invercao
		printf("Proximo Vertice:  %d\n",Retorno); // Imprime o vertice de partida
		printf("\n========================================================================================================================================\n\n");
	}
	if(Retorno == 0){ //se ainda nao acabaram os MME para recolha ou ainda nao atingiu o limite por volta

		for(i=0;i<n;i++){

			if(i!=startnode){ // Verifica se i � diferente do n� de partida

				while(inicioV != NULL){ 
			
					if(inicioV->IdVisitado == i && DistanciaAtual > distance[i]){ //verifica se a variavel i corresponde aos vertices que t�m MME com autonomia abaixo dos 50
						
						while(inicioM != NULL){
							
							if(i == inicioM->vertice && inicioM->Autonomia < 50){ //no vertice em questao verifica quais � que tem autonomia abaixo dos 50
						
								while (Visitados != NULL){ //percorre a estrutura dos vertices visitado para verificar se esse vertice j� foi visitado

									if(Visitados->IdVisitado == inicioM->vertice){ //se o vertice identificado como adjacente ao inic ja ter sido visitado
								
										Percorridos=1; //incrementa o valor 1 a variavel visitado							
									}
									Visitados=Visitados->seguinte; // verifica nos outros vertices visitados
								}
								Visitados=auxVisitados; // volta a colocar o inicio direcionado para o primeiro vertice j� visitado
								if(Percorridos == 0){ //se o vertice identificado como adjacente ao inic n�o ter sido visitado
								
									ModEstado=inicioV; //grava a memoria onde est� o vertice que tinha MME com autonomia baixa
									VerticeSeguinte	= i; //grava o vertice selecionado
									DistanciaAtual = distance[i]; //grava a distancia total para chegar a ele
									AuxiliarContagemVertice ++; //incrementa 1 na variavel AuxiliarContagemVertice
								}
								Percorridos = 0; //faz reset a variavel
					
							}
							inicioM=inicioM->seguinte; // verifica nos outros MME
						}
						inicioM=auxM; // volta a colocar o inicio direcionado para o primeiro MME
					}
					inicioV=inicioV->seguinte; // verifica nos outros vertices com MME com autonomia baixa
				}
				inicioV=auxV; // volta a colocar o inicio direcionado para o primeiro MME com autonomia baixa
			}
		}
		inicioM=auxM; // volta a colocar o inicio direcionado para o primeiro MME
		if(AuxiliarContagemVertice != 0){ //se existir vertice seguinte
			
			ModEstado->IdVisitado = 0; //elimina o vertice da necessidade de visitar
			DistanciaTotal= distance[VerticeSeguinte]; //grava a distancia total para atingir o vertice seguinte
			Visitados=InserirVisitado (Visitados, VerticeSeguinte); //vai adicionar a estrutura o proximo vertice
			auxVisitados=Visitados; //grava na variavel auxiliar
		}
		while(inicioM != NULL){

			if(inicioM->vertice == VerticeSeguinte && inicioM->Autonomia < 50){ //se o vertice do MME for igual ao vertice que necessitamos e tiver autonomia abaixo dos 50
				
				j=VerticeSeguinte;
				do{
					
					j=pred[j]; // Obt�m o predecessor do v�rtice atual
					if(j != UltimoVertice){ // Verifica se o v�rtice atual n�o � o �ltimo v�rtice visitado
						
						Invercao=InserirVisitado (Invercao, j); // Insere o v�rtice atual na estrutura Invercao
					}
				}while(j!=startnode); // Repete o loop enquanto o v�rtice atual n�o for o n� inicial "startnode"
				while(Invercao != NULL){
					
					printf("Proximo Vertice:  %d\n",Invercao->IdVisitado); // Imprime o pr�ximo v�rtice visitado
					printf("\n========================================================================================================================================\n\n");
					Invercao=Invercao->seguinte; // mostra os outros vertices do caminho
				}
				printf("Proximo Vertice:  %d\n\n",VerticeSeguinte); // imprime o proximo vertice e seus respetivos MMEs
				Invercao=NULL;
				UltimoVertice=VerticeSeguinte;
				printf("ID: %d\t"
				"Marca: %s\t"
				"Modelo: %s\t"
				"Autonomia: %d\t"
				"Localizacao: %s\t\t"
				"Custo: %d\t", inicioM->ID, inicioM->Marca, inicioM->Modelo, inicioM->Autonomia, inicioM->Localizacao, inicioM->Custo);
    			printf("\n\n========================================================================================================================================\n\n");
    			NumeroMME++; //incrementa 1 no total de MME para recolher na volta
				inicioTC=InserirTCamiao (inicioTC, inicioM->vertice, NumeroMME, DistanciaTotal); // Insere os dados para contabilizar o limite de MME distancias a percorrer e vertice que ficou
			}
			inicioM=inicioM->seguinte; // verifica nos outros MMEs
		}
		AuxiliarContagemVertice=0; //faz reset a variavel
	}
	return (inicioTC); //retorna o novo ponteiro
}

	//////////////////////////////////////////////////////////////
	
void caminhorecolha (distancia* inicioD, aluguer* inicioAl, mme* inicioM, int inic, int nvertices){ //fun��o de recolha dos MMEs
	
	distancia* auxD=inicioD; mme* auxM=inicioM;
	visitado* inicioV=NULL; visitado* auxV=NULL;
	tcamiao* inicioTC=NULL; tcamiao* auxTC=NULL;
	int totalvertice=0, verticeinicial=inic, visitado=0, DistTotalRecolha=0, DistRecolha=0, DistRetorno=0, VerticesEncontrados=0;
	printf("\n\n\nInicio no vertice %d\n",verticeinicial);
	printf("\n========================================================================================================================================\n\n");
	inicioV=InserirVisitado (inicioV, inic); // Adiciona o primeiro v�rtice � estrutura de visitados
	inicioTC=InserirTCamiao (inicioTC, 0, 0, 0); // Inicializa a estrutura do cami�o
	auxV=inicioV; //vai colocar o seu valor na variavel auxiliar
	while(inicioM != NULL){
		
		while (inicioV != NULL){ //percorre a estrutura dos vertices visitado para verificar se esse vertice j� foi visitado
		
			if(inicioV->IdVisitado == inicioM->vertice){ //se o ID identificado como adjacente ao inic ja ter sido visitado
		
				visitado=1; //incrementa o valor 1 a variavel visitado
			}
			inicioV=inicioV->seguinte; // verifica nos outros vertices visitados
		}
		inicioV=auxV; // volta a colocar o inicio direcionado para o primeiro vertice que necessita de ser visitado
		if(visitado == 0 && inicioM->Autonomia < 50){ //se o vertice adjacente nunca foi visitado
			
			inicioV=InserirVisitado (inicioV, inicioM->vertice); //vai adicionar a estrutura o proximo vertice
			totalvertice ++; //incrimenta 1 no total de vertices com MME
			auxV=inicioV; //vai colocar o seu valor na variavel auxiliar
		}
		visitado=0; //faz reset a variavel
		inicioM=inicioM->seguinte; // verifica nos outros vertices visitados
	}
	inicioM=auxM; // volta a colocar o inicio direcionado para o primeiro MME
	while (totalvertice != VerticesEncontrados){ //enquanto n�o visitar todos os vertices que necessitam de recolha

		if(VerticesEncontrados != totalvertice && inicioTC->NumeroMME != 5){ //se ainda nao acabaram os MME para recolha ou ainda nao atingiu o limite por volta

			inicioTC=dijkstracamiao(nvertices, inic, totalvertice, inicioD, inicioAl, inicioM, inicioV,0,inicioTC); //verifica qual o vertice que necessita de recolha mais perto e retorna o valor alusivo a estrutura dele
			auxTC = inicioTC; //vai colocar o seu valor na variavel auxiliar
			inic = inicioTC->IdVUltimoV; //direciona o vertice de inicio ao novo vertice
			DistRecolha=DistRecolha+inicioTC->DistanciaTotal; //adiciona ao total de distancia de recolha
			VerticesEncontrados++; //incrementa 1
		}
		if(VerticesEncontrados == totalvertice){ //se ja acabaram os MME para recolha
	
			inicioTC=dijkstracamiao(nvertices, inic, totalvertice, inicioD, inicioAl, inicioM, inicioV,verticeinicial,inicioTC); //verifica qual o caminho mais perto para a origem e retorna o valor alusivo a estrutura dele
			auxTC = inicioTC; //vai colocar o seu valor na variavel auxiliar
			inic=inicioTC->IdVUltimoV; //direciona o vertice de inicio ao novo vertice
			DistRetorno=DistRetorno+inicioTC->DistanciaTotal; //adiciona ao total de distancia de retorno a origem
		}
		if(inicioTC->NumeroMME == 5){ //se ja atingiu o limite de MMEs por volta

			inicioTC=dijkstracamiao(nvertices, inic, totalvertice, inicioD, inicioAl, inicioM, inicioV,verticeinicial,inicioTC); //verifica qual o caminho mais perto para a origem e retorna o valor alusivo a estrutura dele
			printf("\n\n\n\n=============================================Proxima recolha============================================================================\n\n");
			printf("\n\nInicio no vertice %d\n",verticeinicial); 
			printf("\n========================================================================================================================================\n\n");
			inic=verticeinicial; //direciona o vertice de inicio a origem
			DistRetorno=DistRetorno+inicioTC->DistanciaTotal; //adiciona ao total de distancia de retorno a origem
			inicioTC->NumeroMME=0; //faz reset a variavel para nova contagem do limite
		}	
	}
	DistTotalRecolha=DistRetorno+DistRecolha; //cria uma estatistica das distancias
	printf("\n\n\n\n===================================Estatistica==========================================================================================\n");
	printf("========================================================================================================================================\n");
	printf("Distancia total dos trajetos de recolha sem retornos: %d\n\n",DistRecolha); 
	printf("========================================================================================================================================\n");
	printf("Distancia total dos trajeto de retorno: %d\n\n",DistRetorno); 
	printf("========================================================================================================================================\n");
	printf("Distancia total dos trajeto de recolha com retorno: %d\n\n\n",DistTotalRecolha); 
}

