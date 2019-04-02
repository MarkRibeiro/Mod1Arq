#include <stdio.h>
#include <stdlib.h>

/***************************************************************************
*  $MCI Módulo de definição: Módulo Lista
*
*  Arquivo gerado:              LISTA.C
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Trabalho 1 INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: Caio Melo, Mark Ribeiro
*
*  $ED Descrição do módulo
*     Este módulo implementa as funções e tipos relativos a lista encadeada de 
	  inteiros presente em cada folha da arvore. Existem apenas duas funções,
	  uma que cria e retorna a lista encadeada de inteiros que são recebidos 
	  nos parâmetros, e uma que simplesmente recebe uma lista encadeada de 
	  inteiros e a printa.
***************************************************************************/

/*Typedef da struct noLista, que representa a lista encadeada de inteiros*/
typedef struct noLista NoLista;

/***********************************************************************
*
*  $FC Função: LIS Cria Lista
*
*  $ED Descrição da função
*     Cria e retorna a lista encadeada de inteiros que são recebidos 
	  nos parâmetros.
*
***********************************************************************/

NoLista* LIS_Cria(int n1, int n2, int n3);


/***********************************************************************
*
*  $FC Função: LIS Printa Lista
*
*  $ED Descrição da função
*     Recebe uma lista encadeada de 
	  inteiros e a printa.
*
***********************************************************************/

void LIS_Printa(NoLista* No);

/********** Fim do módulo de definição: Módulo lista **********/