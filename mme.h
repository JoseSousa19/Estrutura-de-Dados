
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
	int ID; //ID de identificação dos Meios de Mobilidade Eletrica
    char Marca[20]; // Marca dos Meios de Mobilidade Eletrica
    char Modelo[20]; // Modelo dos Meios de Mobilidade Eletrica
    int Autonomia; // Autonomia dos Meios de Mobilidade Eletrica
    char Localizacao[40]; // Localização dos Meios de Mobilidade Eletrica
    int Custo; // Localização dos Meios de Mobilidade Eletrica
    int vertice; //Vertice correspondente a localização
    struct MME* seguinte;
}mme;

typedef struct Aluguer{ //Definir a estrutura dos Alugueres
	int IDcliente; //ID de identificação do cliente
    int IDmme; // ID de identificação dos Meios de Mobilidade Eletrica
    int Aativo; //Estado do aluguer
    struct Aluguer* seguinte;
}aluguer;

mme* InserirMME (mme* inicio, int ID, char Marca[], char Modelo[], int Autonomia, char Localizacao[], int Custo, int vertice); //Função para adicionar novos MME

aluguer* InserirAluguer (aluguer* inicio, int IDcliente, int IDmme, int Aativo); //Função para adicionar novos alugueres

int VerticeCorrespondente (char palavra[40]); //Função para verificar o vertice correspondente a localização

char* AdicionarLocalizacaoNova (); //Função para inserir localização do MME corretamente

mme* AdicionarMME(mme* inicioM); //Função para Adicionar novos Meios de Mobilidade Eletrica

aluguer* AlugarMME(int Acessor, mme* inicioM, aluguer* inicioA, cliente* inicioC); //Função de Adicionar um novo aluguer

mme* RemoverMME(mme* inicioM); //Função para remover um MME

void VisualizarMME(mme* inicioM); //Função para vizualizar MMEs já previamente inseridos

void atualizarMME(mme* inicioM); //Função para atualizar os colaboradores já inscritos

void HistoricoAluguerMME(aluguer* inicioA ,mme* inicioM, cliente* inicioC); //Função para verificar os historicos de aluguer de MME

void PercentagemMMEAlugados(aluguer* inicioA ,mme* inicioM); //Função para determinar a percentagem de MME alugados

void AtualizarEstadoAluguer(aluguer* inicioA, int Acessor,mme* inicioM ); //Função para terminar aluguer

void DecrescenteAutonomia(mme* inicioM); //Função para determinar a ordem decrescente de autonomia

int PesquisaPorLocalizacao(mme* inicioM); //Função os MMEs mais pertos e suas distancias

void CarregarSaldo(cliente* inicioC, int Acessor); //Função para carregar saldo do cliente

void HistoricoCliente(int Acessor, mme* inicioM, aluguer* inicioA); //Função para mostrar historico do cliente

void MMEsemAluguer(mme* inicioM, aluguer* inicioA); //Função para verificar os MMEs sem aluguer ativo

#endif 
