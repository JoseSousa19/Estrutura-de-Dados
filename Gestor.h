#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <ctype.h>
#ifndef Gestor_H_INCLUDED
#define Gestor_H_INCLUDED



typedef struct Gestor{ //Definir a estrutura do Gestor
	int ID; //ID de identificação do Gestor
    char Nome[20]; // Nome do Gestor
    char Morada[20]; // Morada do Gestor
    char Pass[20]; //Pass do gestor
    struct Gestor* seguinte; //interliga a nova memoria com a antiga
}gestor;

gestor* InserirGestor (gestor* inicio, int ID, char Nome[], char Morada[], char Pass[]); //Adicionar novos gestores

gestor* AdicionarGestor(gestor* inicioG); //Função para Adicionar um novo Gestor

gestor* RemoverGestor(gestor* inicioG); //Função para remover um gestor escolhido

void VisualizarGestor(gestor* inicioG); //Função para vizualizar gestores já previamente inseridos

void atualizarGestor(gestor* inicioG, int Acessor); //Função para atualizar os gestores já inscritos

#endif 
