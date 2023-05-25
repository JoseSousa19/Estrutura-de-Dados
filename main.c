#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "Gestor.h"
#include "cliente.h"
#include "mme.h"
#include "distancias.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	cliente* inicioC=NULL; // Ponteiro para o início da lista de clientes
	gestor* inicioG=NULL; // Ponteiro para o início da lista de gestores
	mme* inicioM=NULL; // Ponteiro para o início da lista de meios de mobilidade elétrica (MME)
	aluguer* inicioAl=NULL; // Ponteiro para o início da lista de alugueres
	distancia* inicioD=NULL; // Ponteiro para o início da lista de distâncias
	distancia* auxD=NULL; // Ponteiro auxiliar para manipulação da lista de distâncias
	cliente* auxC=NULL; // Ponteiro auxiliar para manipulação da lista de clientes
	gestor* auxG=NULL; // Ponteiro auxiliar para manipulação da lista de gestores
	aluguer* auxAl=NULL; // Ponteiro auxiliar para manipulação da lista de alugueres
	mme* auxM=NULL; // Ponteiro auxiliar para manipulação da lista de meios de mobilidade elétrica (MME)

	//////////////////////////////////////////////////////////////

	FILE *Fclientes; // Ponteiro para o arquivo "Gestao de Clientes.txt"
	FILE *Fgestor; // Ponteiro para o arquivo "Gestao de Gestores.txt"
	FILE *Fmme; // Ponteiro para o arquivo "Gestao de Meios de Mobilidade Eletrica.txt"
	FILE *Faluguer; // Ponteiro para o arquivo "Gestao de Aluguer de Meios de Mobilidade Eletrica.txt"
	FILE *Fdistancia; // Ponteiro para o arquivo "Gestao de Distancias.txt"

	//////////////////////////////////////////////////////////////

	char Nome[20], Morada[20], Marca[20], Modelo[20], Pass[20], Localizacao[40];
	int ID, IDcliente, IDmme, NIF, Saldo, Autonomia, Custo, Aativo, IdOrigem, IdDestino, Distancia;
	int Acessor=0, aux=0, vertice=0, Nvertices=0;

	//////////////////////////////////////////////////////////////

	Fclientes=fopen("Gestao de Clientes.txt","r"); // Abre o arquivo "Gestao de Clientes.txt" somente para leitura (se não existir, é criado)
	while(fscanf(Fclientes,"%d ; %[^;]; %[^;]; %d ; %d ; %s", &ID, Nome, Morada, &NIF, &Saldo, Pass)!= EOF) { // Enquanto ainda existirem caracteres no arquivo, ele:
		
		inicioC=InserirCliente(inicioC, ID, Nome, Morada, NIF, Saldo, Pass); // Insere um novo cliente na lista
	}
	fclose(Fclientes); // Fecha o arquivo "Gestao de Clientes.txt"

	Fgestor=fopen("Gestao de Gestores.txt","a+"); // Abre o arquivo "Gestao de Gestores.txt" somente para leitura (se não existir, é criado)
	while(fscanf(Fgestor,"%d ; %[^;]; %[^;]; %s", &ID, Nome, Morada, Pass)!= EOF) { // Enquanto ainda existirem caracteres no arquivo, ele:
		
		inicioG=InserirGestor(inicioG, ID, Nome, Morada, Pass); // Insere um novo gestor na lista
	}
	fclose(Fgestor); // Fecha o arquivo "Gestao de Gestores.txt"

	Fmme=fopen("Gestao de Meios de Mobilidade Eletrica.txt","a+"); // Abre o arquivo "Gestao de Meios de Mobilidade Eletrica.txt" somente para leitura (se não existir, é criado)
	while(fscanf(Fmme,"%d ; %[^;]; %[^;]; %d ; %[^;]; %d ; %d", &ID, Marca, Modelo, &Autonomia, &Localizacao, &Custo, &vertice)!= EOF) { // Enquanto ainda existirem caracteres no arquivo, ele:
		
		inicioM=InserirMME(inicioM, ID, Marca, Modelo, Autonomia, Localizacao, Custo, vertice); // Insere um novo MME na lista
	}
	fclose(Fmme); // Fecha o arquivo "Gestao de Meios de Mobilidade Eletrica.txt"

	Faluguer=fopen("Gestao de Aluguer de Meios de Mobilidade Eletrica.txt","a+"); // Abre o arquivo "Gestao de Aluguer de Meios de Mobilidade Eletrica.txt" somente para leitura (se não existir, é criado)
	while(fscanf(Faluguer,"%d ; %d ; %d", &IDcliente, &IDmme, &Aativo)!= EOF) { // Enquanto ainda existirem caracteres no arquivo, ele:
		
		inicioAl=InserirAluguer(inicioAl, IDcliente, IDmme, Aativo); // Insere um novo aluguer na lista
	}
	fclose(Faluguer); // Fecha o arquivo "Gestao de Aluguer de Meios de Mobilidade Eletrica.txt"

	Fdistancia=fopen("Gestao de Distancias.txt","a+"); // Abre o arquivo "Gestao de Distancias.txt" somente para leitura (se não existir, é criado)
	while(fscanf(Fclientes,"%d ; %d; %d;", &IdOrigem, &IdDestino, &Distancia, Localizacao)!= EOF) { // Enquanto ainda existirem caracteres no arquivo, ele:
		
		inicioD=InserirDistancias(inicioD, IdOrigem, IdDestino, Distancia); // Insere uma nova distância na lista
		if (IdOrigem > Nvertices) {
		
			Nvertices=IdOrigem; // Atualiza o número de vértices
		}
		if (IdDestino > Nvertices) {
		
			Nvertices=IdDestino; // Atualiza o número de vértices
		}
	}
	Nvertices ++;
	
	fclose(Fdistancia); // Fecha o arquivo "Gestao de Distancias.txt"

	////////////////////////////////////////////////////////////// 
     
   auxC = inicioC; // Ponteiro auxiliar para percorrer a lista de clientes
	auxG = inicioG; // Ponteiro auxiliar para percorrer a lista de gestores
	auxD = inicioD; // Ponteiro auxiliar para percorrer a lista de distâncias
	inicioG = auxG; // Define o início da lista de gestores como o ponteiro auxiliar
	inicioC = auxC; // Define o início da lista de clientes como o ponteiro auxiliar

	while (aux == 0) { // Loop para solicitar login
	
    	printf("\n              =========            ");
    	printf("\n  ============|=Login=|============");
    	printf("\n  =================================\n\n");
    	printf("  ->       ID : ");
    	scanf("%d", &ID);
    	setbuf(stdin, NULL);
    	printf("  \n");
    	printf("  ->       Pass : ");
    	scanf("%s", &Pass);
    	setbuf(stdin, NULL);	
    
		while (inicioC != NULL && aux==0){ //Atraves do ciclo conseguimos visualizar todos os clientes para verificar o login

    		if (inicioC->ID == ID && strcmp(inicioC->Pass, Pass)==0){ //se o ID e a Pass foram iguais entra no menu de login
    		
				Acessor=inicioC->ID; 
				inicioC=auxC;  
				while(aux==0){	//enquanto não pedir para sair vai estar sempre em loop
			
					system("cls");
					printf("\n                                            ========                                          ");
					printf("\n  ==========================================|=Menu=|==========================================");
    				printf("\n  ============================================================================================\n"
		   			"  **|                                                                                      |**\n");
    				printf("  **|		     =======(A)  Alugar um Meio de Mobilidade Eletrica                     |**\n"
		   			"  **|                =======(B)  Carregar Saldo da Conta                                   |**\n"
		   			"  **|                =======(C)  Consultar Saldo                                           |**\n"
		  			 "  **|                =======(D)  Consultar Dados                                           |**\n"
	      			 "  **|                =======(E)  Alterar Dados da Conta                                    |**\n"
		  			 "  **|                =======(F)  Verificar Meios de Mobilidade Eletrica Disponiveis        |**\n"
		 			  "  **|                =======(G)  Consultar Historico de Aluguer                            |**\n"
		 			  "  **|                =======(H)  Remover Conta                                             |**\n"
			  		 "  **|                =======(I)  Terminar Aluguer                                          |**\n"
			 		  "  **|                =======(J)  Verificar por Ordem Decrescente de Autonomia              |**\n"
			 		  "  **|                =======(K)  Pesquisar Meios de Mobilidade Eletrica por Localizacao    |**\n"
			 		  "  **|                =======(S)  Sair                                                      |**\n"
			 		  "  **|                                                                                      |**\n"
			 		  "  ============================================================================================\n\n");
				   
					char opcao;
					printf("\nOpcao escolhida: ");
					scanf("%c", &opcao);
					switch (opcao){
						
	        			case 'A':
	            			system("cls");
	                		inicioAl=AlugarMME(Acessor,inicioM,inicioAl,inicioC); //Função de Adicionar um novo aluguer
							break;
	            
	            		case 'B':
	            			system("cls");
	                		CarregarSaldo(inicioC, Acessor); //Função para carregar saldo do cliente
	             	   		break;
	            	
	           	 		case 'C':
	            			system("cls");
	            			auxC=inicioC;
	 						while (inicioC != NULL){
	 							
								if(Acessor == inicioC->ID){ // Comparamos se o id é o certo
								
									printf("O seu Saldo e: %d \n",inicioC->Saldo); //mostramos o saldo
									Sleep(1000);
								}
								inicioC=inicioC->seguinte;
							}
							system("PAUSE");
							inicioC=auxC;
	            			break;
	                
		            	case 'D':
	    	        		system("cls");
	    	        		auxC=inicioC;
	        	    		while (inicioC != NULL){
	        	    			
								if(Acessor == inicioC->ID){ // Comparamos se o id é o certo
									
	        	    				printf("ID: %d\n", inicioC->ID);
	        						printf("Nome: %s\n", inicioC->Nome);
		        					printf("Morada: %s\n", inicioC->Morada);
	    	    					printf("NIF: %d\n", inicioC->NIF);
	       		 					printf("Saldo: %d\n", inicioC->Saldo); 
	       		 				}
							inicioC=inicioC->seguinte;
							}
	        				system("PAUSE");
	        				inicioC=auxC;
	        				break;
	            	
		            	case 'E':
	    	        		system("cls");
	        	    		atualizarCliente(inicioC, Acessor); //Função para atualizar os colaboradores já inscritos
	            			break;
	            	
		            	case 'F':
	    	        		system("cls");
	        	    		MMEsemAluguer(inicioM, inicioAl); //Função para verificar os MMEs sem aluguer ativo
	            			system("PAUSE");
	            			break;
	            
	    	     	   case 'G':
	        		    	system("cls"); 
	          		  		HistoricoCliente(Acessor, inicioM, inicioAl); //Função para mostrar historico do cliente
	          		  		system("PAUSE");
	            			break;
	            	
		        	    case 'H':
		        	    	system("cls");
	 		    	       	inicioC=RemoverClientes(inicioC, Acessor); //Função para remover um clientes
	  		    	      	aux=1;
	    	    	    	break;
	            	
	       			     case 'I':
	            			system("cls");
	            			AtualizarEstadoAluguer(inicioAl, Acessor,inicioM); //Função para terminar aluguer
	            			break;
	            
	            	 	case 'J':
	            			system("cls");
	            			DecrescenteAutonomia(inicioM); //Função para determinar a ordem decrescente de autonomia
	            			system("PAUSE");
	            			break;
	            	
	            	 	case 'K':
	            			system("cls");
	            			int local=0, verticeperto=0, apoio=1;
	            			auxAl=inicioAl;
	            			auxM=inicioM;
	            			auxD=inicioD;
	            			int Matriz[VERTICES][VERTICES]; // Matriz de adjacência
	    					Adjacentes Grafo1[VERTICES];  // Lista de adjacência
	 						inicializarGrafo(Grafo1); // Inicializa o grafo
	    
	    					while (inicioD != NULL)	{
	    						
	    						inserirAresta(Grafo1,inicioD->IdOrigem,inicioD->IdDestino,inicioD->Distancia); // Insere arestas no grafo
	    						inicioD=inicioD->seguinte;
							}
							inicioD=auxD;
							converter(Grafo1, Matriz); // Converte a lista de adjacência para matriz de adjacência
							local=PesquisaPorLocalizacao(inicioM); // Obtém a localização a pesquisar
							verticeperto=dijkstra(Matriz,VERTICES,local,inicioM,inicioAl); // Executa o algoritmo de Dijkstra
							while (inicioM != NULL){
								
	    						if (verticeperto == inicioM->vertice && inicioM->Autonomia > 25){ // Verifica se o vértice corresponde ao mais próximo
	    						
	    							while (inicioAl != NULL){
	    							
										if(inicioAl->IDmme == inicioM->ID && inicioAl->Aativo == 1){
										
											apoio = 0; // Se o meio de mobilidade já estiver alugado, apoio é definido como 0
	        							}
	        							inicioAl = inicioAl->seguinte;
									}	
									printf("vertice: %d\n", inicioM->vertice);
								
									if (apoio == 1){
									
	        							printf("ID: %d\n", inicioM->ID); // Se apoio for igual a 1, o meio de mobilidade está disponível para aluguel
	        							printf("Marca: %s\n", inicioM->Marca);
	        							printf("Modelo: %s\n", inicioM->Modelo);
	        							printf("Autonomia: %d\n", inicioM->Autonomia);
	        							printf("Localizacao: %s\n", inicioM->Localizacao);
	        							printf("Custo: %d\n", inicioM->Custo);
	        							printf("\n\n");
									}
									apoio = 1; // Reseta o valor de apoio para a próxima iteração
									inicioAl=auxAl; // Reinicia a lista de alugueres
								}
	    						inicioM = inicioM->seguinte;
							}
							inicioM=auxM;
							system("PAUSE");
	            			break;
	            	
	            		case 'S':
	            			system("cls");
	            			printf("\nSaindo...");
	            			printf("\nObrigado Pela Preferencia");
	                		Sleep(1000);
	                		aux=1;
	                		break;
	        		}
	    		}	
				
			}
			if(aux!=1){
				
				inicioC=inicioC->seguinte;
			}
		}
		
		while (inicioG != NULL && aux==0){ //Atraves do ciclo conseguimos visualizar todos os gestores para verificar o login
		
			if((inicioG->ID == ID ) && strcmp(inicioG->Pass, Pass)==0){ //se o ID e a Pass foram iguais entra no menu de login
				Acessor=inicioG->ID;
				inicioG=auxG;
				inicioC=auxC;	   
				while(aux==0){	 //enquanto não pedir para sair vai estar sempre em loop
				
					system("cls");
					printf("\n                                            ========                                          ");
					printf("\n  ==========================================|=Menu=|==========================================");
	    			printf("\n  ============================================================================================\n"
			   		"  **|                                                                                      |**\n");
	    			printf("  **|		     =======(A)   Adicionar Gestor                                         |**\n"
			  	 	"  **|                =======(B)   Adicionar Cliente                                        |**\n"
			   		"  **|                =======(C)   Adicionar Meio de Mobilidade Eletrica                    |**\n"
			   		"  **|                =======(D)   Consultar Clientes                                       |**\n"
		       		"  **|                =======(E)   Consultar Meio de Mobilidade Eletrica                    |**\n"
			   		"  **|                =======(F)   Consultar Gestores                                       |**\n"
					"  **|                =======(G)   Alterar Dados de Gestor                                  |**\n"
			   		"  **|                =======(H)   Alterar Dados de Cliente                                 |**\n"
			  	 	"  **|                =======(I)   Alterar Dados de Meio de Mobilidade Eletrica             |**\n"
			   		"  **|                =======(J)   Remover Gestor                                           |**\n"
			   		"  **|                =======(K)  Remover Cliente                                           |**\n"
			   		"  **|                =======(L)  Remover Meio de Mobilidade Eletrica                       |**\n"
			   		"  **|                =======(M)  Historico de Aluger de Meio de Mobilidade Eletrica        |**\n"
			   		"  **|                =======(N)  Percentagem de Meio de Mobilidade Eletrica Alugados       |**\n"
			   		"  **|                =======(O)  Consultar Mapa de Distancias                              |**\n"
			   		"  **|                =======(P)  Adicionar Novo trajeto                                    |**\n"
			   		"  **|                =======(Q)  Adicionar Novo trajeto                                    |**\n"
			   		"  **|                =======(S)  Sair                                                      |**\n"
			   		"  **|                                                                                      |**\n"
			   		"  ============================================================================================\n\n");	   
					int clientepre = 0;
					char opcao;
					printf("\nOpcao escolhida: ");
					scanf("%c", &opcao);
					setbuf(stdin, NULL);
					switch (opcao){
						
	        			case 'A':
	            			system("cls");
	                		inicioG=AdicionarGestor(inicioG); //Função para Adicionar um novo Gestor
	                		break;
	            
	            		case 'B':
	            			system("cls");
	                		inicioC=AdicionarCliente(inicioC); //Função para Adicionar um novo Cliente
	                		break;
	            	
	           			case 'C':
	            			system("cls");
	            			inicioM=AdicionarMME(inicioM); //Função para Adicionar novos Meios de Mobilidade Eletrica
	            			break;
	                
	            		case 'D':
	            			system("cls");
	            			VisualizarClientes(inicioC); //Função para vizualizar clientes já previamente inseridos
	        				system("PAUSE");
	        				break;
	            	
	            		case 'E':
	            			system("cls");
	            			VisualizarMME(inicioM); //Função para vizualizar MMEs já previamente inseridos
	            			system("PAUSE");
	            			break;
	            		
	            		case 'F':
	            			system("cls");
	            			VisualizarGestor(inicioG); //Função para vizualizar gestores já previamente inseridos
	            			system("PAUSE");
	            			break;
	            	
	            		case 'G':
	            			system("cls");
	            			atualizarGestor(inicioG, Acessor); //Função para atualizar os gestores já inscritos
	            			break;
	            
	            		case 'H':
	            			system("cls");
							printf("Introduza o ID do Cliente a ser atualizado: ");
							scanf("%d", &clientepre);
							auxC=inicioC;
							while (inicioC != NULL){
								
	       						if(inicioC->ID==clientepre){
	       							
									atualizarCliente(inicioC, clientepre); //Função para atualizar os colaboradores já inscritos
								}	
								inicioC=inicioC->seguinte;		
							}	
							inicioC=auxC;
	            			break;
	            	
	            		case 'I':
	            			system("cls");
	            			atualizarMME(inicioM); //Função para atualizar os colaboradores já inscritos
	            			break;
	            	
	            		case 'J':
	            			system("cls");
	            			RemoverGestor(inicioG); //Função para remover um gestor escolhido
	            			break;
	            	
	           			case 'K':
	            			system("cls");
	            			int numero = 0;
							printf("Introduza o ID do Cliente a ser eliminado: ");
							scanf("%d", &numero);
	            			inicioC=RemoverClientes(inicioC, numero); //Função para remover um clientes
	            			break;
	            
	            		case 'L':
	            			system("cls");
	            			inicioM=RemoverMME(inicioM); //Função para remover um MME
	            			break;
	            
	            		case 'M':
	            			system("cls");
	            			HistoricoAluguerMME(inicioAl, inicioM, inicioC); //Função para verificar os historicos de aluguer de MME
	            			system("PAUSE");
	            			break;
	            
	            		case 'N':
	            			system("cls");
	            			PercentagemMMEAlugados(inicioAl, inicioM); //Função para determinar a percentagem de MME alugados
	            			system("PAUSE");
	            			break;
	            			
	            		case 'O':
	            			system("cls");
	            			VisualizarDistancas(inicioD); //Vizualiza as estradas/distancias já previamente inseridos
	            			system("PAUSE");
	            			break;
	            			
	            		case 'P':
	            			system("cls");
	            			inicioD=AdicionarNovaDistancia(inicioD); //Adicionar novas distancias
	            			system("PAUSE");
	            			break;
	            			
	            		case 'Q':
	            			system("cls");
	            			caminhorecolha (inicioD,inicioAl,inicioM, 1,Nvertices); //função de recolha dos MMEs
	            			system("PAUSE"); 
	            			break;
	            	
	            		case 'S':
	            			system("cls");
	            			printf("\nSaindo...");
	            			printf("\nObrigado Pela Preferencia");	
	                		aux=1;
	                		break;  
	        		}
	    		}
			}
			if(aux!=1){
				
				inicioG=inicioG->seguinte;
			}
		}
		if(aux==0){
			
			printf("Nome ou Palavra Pass errados\n");
			Sleep(2000);
			system("cls");
		}
	}  
	  
	//////////////////////////////////////////////////////////////   	

	Fclientes=fopen("Gestao de Clientes.txt","w"); //Abre o arquivo somente para escrita (se já existir, apaga seu conteúdo)
	while (inicioC != NULL){
		
    	fprintf(Fclientes,"%d ; %s; %s; %d ; %d ; %s\n",
            inicioC->ID,
            inicioC->Nome, 
            inicioC->Morada, 
            inicioC->NIF, 
            inicioC->Saldo, 
            inicioC->Pass );
    	inicioC=inicioC->seguinte;
	}
	fclose(Fclientes);

	Fgestor=fopen("Gestao de Gestores.txt","w"); //Abre o arquivo somente para escrita (se não existir é criado ou truncado)
	while (inicioG != NULL){
		
    	fprintf(Fgestor,"%d ; %s; %s; %s\n",
        	inicioG->ID, 
        	inicioG->Nome, 
        	inicioG->Morada, 
        	inicioG->Pass);
   		inicioG=inicioG->seguinte;
	}
	fclose(Fgestor);
				
	Fmme=fopen("Gestao de Meios de Mobilidade Eletrica.txt","w"); //Abre o arquivo para escrita (se não existir é criado)
	while (inicioM != NULL){
		
		fprintf(Fmme,"%d ; %s; %s; %d ;%s; %d; %d\n",
			inicioM->ID, 
			inicioM->Marca, 
			inicioM->Modelo, 
			inicioM->Autonomia, 
			inicioM->Localizacao, 
			inicioM->Custo,
			inicioM->vertice);
		inicioM=inicioM->seguinte;
	}
	fclose(Fmme);

	Faluguer=fopen("Gestao de Aluguer de Meios de Mobilidade Eletrica.txt","w"); //Abre o arquivo para escrita (se não existir é criado)
	while (inicioAl != NULL){
		
		fprintf(Faluguer,"%d ; %d ; %d\n",
			inicioAl->IDcliente,
			inicioAl->IDmme,
			inicioAl->Aativo );
		inicioAl=inicioAl->seguinte;
	}							
	fclose(Faluguer);   
	
	Fdistancia=fopen("Gestao de Distancias.txt","w"); //Abre o arquivo para escrita (se não existir é criado)
	while (inicioD != NULL){
		
		fprintf(Faluguer,"%d ; %d; %d;\n",
			inicioD->IdOrigem,
			inicioD->IdDestino,
			inicioD->Distancia );
		inicioD=inicioD->seguinte;
	}							
	fclose(Fdistancia);           
	return 0;
}
