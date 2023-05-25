#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>
#ifndef cliente_H_INCLUDED
#define cliente_H_INCLUDED

typedef struct Cliente{ //Definir a estrutura do Cliente
	int ID; //ID de identificação do Cliente
    char Nome[20]; // Nome do Cliente
    char Morada[20]; // Morada do Cliente
    int NIF; //NIF do Cliente
    int Saldo; //Saldo do Cliente
    char Pass[20]; //Pass do Cliente
    struct Cliente* seguinte; //interliga a nova memoria com a antiga
}cliente;

cliente* InserirCliente (cliente* inicioC, int ID, char Nome[], char Morada[], int NIF, int Saldo, char Pass[]); //Função para adicionar novos clientes

cliente* AdicionarCliente(cliente* inicioC); //Função para Adicionar um novo Cliente

cliente* RemoverClientes(cliente* inicioC,int numero); //Função para remover um clientes

void VisualizarClientes(cliente* inicioC); //Função para vizualizar clientes já previamente inseridos

void atualizarCliente(cliente* inicioC, int Acessor); //Função para atualizar os colaboradores já inscritos

#endif 

