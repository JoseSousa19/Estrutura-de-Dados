#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#ifndef distancias_H_INCLUDED
#define distancias_H_INCLUDED
#define VERTICES 10
#include "mme.h"

typedef struct Distancia{ //Definir a estrutura da rede de estradas
	int IdOrigem; //vertice de origem
    int IdDestino; //vertice de destino
    int Distancia; // distancia entre vertice
    struct Distancia* seguinte; //interliga a nova memoria com a antiga
}distancia;

typedef struct registo{ //Definir a estrutura da rede de estradas do grafo
	int id; // vertice de destino
 	float peso; // distancia entre vertice
 	struct registo * seguinte; //interliga a nova memoria com a antiga
} Lista, * Adjacentes;

typedef struct Visitado{ //Definir a estrutura dos Vertices visitados
	int IdVisitado; //ID de identificação dos Meios de Mobilidade Eletrica
    struct Visitado* seguinte;
}visitado;

typedef struct TCamiao{ //Definir a estrutura dos transportes de camiao
	int IdVUltimoV; //ID do ultimo vertice visitado
	int NumeroMME; //numero de MME já inseridos no camiao
	int DistanciaTotal; //distancia total do trajeto
    struct TCamiao* seguinte; //interliga a nova memoria com a antiga
}tcamiao;

	//////////////////////////////////////////////////////////////

distancia* InserirDistancias (distancia* inicio, int IdOrigem, int IdDestino, int Distancia); //adicionar novas estradas direcionais

distancia* AdicionarNovaDistancia(distancia* inicioD); //Adicionar novas distancias

void VisualizarDistancas(distancia* inicioD); //Vizualiza as estradas/distancias já previamente inseridos

int inserirAresta(Adjacentes Grafo[],int v1, int v2, float p); //adicionar novas arestas ao grafo

void inicializarGrafo(Adjacentes Grafo[]); //limpa o array grafo ao iniciar

void converter(Adjacentes Grafo[], int Matriz[][VERTICES]); //converte grafos em matrizes

int dijkstra(int G[VERTICES][VERTICES],int n,int startnode,mme* inicioM,aluguer* inicioAl); //encontrar o melhor caminho para cada vertice e a distancia até ao mesmo

visitado* InserirVisitado (visitado* inicio, int IdVisitado); //adiciona novo vertice visitado

tcamiao* InserirTCamiao (tcamiao* inicio, int IdVUltimoV, int NumeroMME, int DistanciaTotal); //adiciona novo caminho de recolha

tcamiao* dijkstracamiao(int n, int startnode, int Nvertices, distancia* inicioD, aluguer* inicioAl, mme* inicioM, visitado* inicioV, int Retorno, tcamiao* inicioTC); //determinar pelo metodo de dijkstra o caminho mais perto para recolha ods MMEs

void caminhorecolha (distancia* inicioD, aluguer* inicioAl, mme* inicioM, int inic, int nvertices); //função de recolha dos MMEs

#endif 

