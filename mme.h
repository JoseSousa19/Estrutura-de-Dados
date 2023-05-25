
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>
#ifndef mme_H_INCLUDED
#define mme_H_INCLUDED
#include "cliente.h"
#include "Gestor.h"

typedef struct MME{ //Definir a estrutura dos Meios de Mobilidade Eletrica
	int ID; //ID de identifica��o dos Meios de Mobilidade Eletrica
    char Marca[20]; // Marca dos Meios de Mobilidade Eletrica
    char Modelo[20]; // Modelo dos Meios de Mobilidade Eletrica
    int Autonomia; // Autonomia dos Meios de Mobilidade Eletrica
    char Localizacao[40]; // Localiza��o dos Meios de Mobilidade Eletrica
    int Custo; // Localiza��o dos Meios de Mobilidade Eletrica
    int vertice; //Vertice correspondente a localiza��o
    struct MME* seguinte;
}mme;

typedef struct Aluguer{ //Definir a estrutura dos Alugueres
	int IDcliente; //ID de identifica��o do cliente
    int IDmme; // ID de identifica��o dos Meios de Mobilidade Eletrica
    int Aativo; //Estado do aluguer
    struct Aluguer* seguinte;
}aluguer;

mme* InserirMME (mme* inicio, int ID, char Marca[], char Modelo[], int Autonomia, char Localizacao[], int Custo, int vertice); //Fun��o para adicionar novos MME

aluguer* InserirAluguer (aluguer* inicio, int IDcliente, int IDmme, int Aativo); //Fun��o para adicionar novos alugueres

int VerticeCorrespondente (char palavra[40]); //Fun��o para verificar o vertice correspondente a localiza��o

char* AdicionarLocalizacaoNova (); //Fun��o para inserir localiza��o do MME corretamente

mme* AdicionarMME(mme* inicioM); //Fun��o para Adicionar novos Meios de Mobilidade Eletrica

aluguer* AlugarMME(int Acessor, mme* inicioM, aluguer* inicioA, cliente* inicioC); //Fun��o de Adicionar um novo aluguer

mme* RemoverMME(mme* inicioM); //Fun��o para remover um MME

void VisualizarMME(mme* inicioM); //Fun��o para vizualizar MMEs j� previamente inseridos

void atualizarMME(mme* inicioM); //Fun��o para atualizar os colaboradores j� inscritos

void HistoricoAluguerMME(aluguer* inicioA ,mme* inicioM, cliente* inicioC); //Fun��o para verificar os historicos de aluguer de MME

void PercentagemMMEAlugados(aluguer* inicioA ,mme* inicioM); //Fun��o para determinar a percentagem de MME alugados

void AtualizarEstadoAluguer(aluguer* inicioA, int Acessor,mme* inicioM ); //Fun��o para terminar aluguer

void DecrescenteAutonomia(mme* inicioM); //Fun��o para determinar a ordem decrescente de autonomia

int PesquisaPorLocalizacao(mme* inicioM); //Fun��o os MMEs mais pertos e suas distancias

void CarregarSaldo(cliente* inicioC, int Acessor); //Fun��o para carregar saldo do cliente

void HistoricoCliente(int Acessor, mme* inicioM, aluguer* inicioA); //Fun��o para mostrar historico do cliente

void MMEsemAluguer(mme* inicioM, aluguer* inicioA); //Fun��o para verificar os MMEs sem aluguer ativo

#endif 
