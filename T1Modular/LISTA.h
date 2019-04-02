#include <stdio.h>
#include <stdlib.h>

/***************************************************************************
*  $MCI M�dulo de defini��o: M�dulo Lista
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
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa as fun��es e tipos relativos a lista encadeada de 
	  inteiros presente em cada folha da arvore. Existem apenas duas fun��es,
	  uma que cria e retorna a lista encadeada de inteiros que s�o recebidos 
	  nos par�metros, e uma que simplesmente recebe uma lista encadeada de 
	  inteiros e a printa.
***************************************************************************/

/*Typedef da struct noLista, que representa a lista encadeada de inteiros*/
typedef struct noLista NoLista;

/***********************************************************************
*
*  $FC Fun��o: LIS Cria Lista
*
*  $ED Descri��o da fun��o
*     Cria e retorna a lista encadeada de inteiros que s�o recebidos 
	  nos par�metros.
*
***********************************************************************/

NoLista* LIS_Cria(int n1, int n2, int n3);


/***********************************************************************
*
*  $FC Fun��o: LIS Printa Lista
*
*  $ED Descri��o da fun��o
*     Recebe uma lista encadeada de 
	  inteiros e a printa.
*
***********************************************************************/

void LIS_Printa(NoLista* No);

/********** Fim do m�dulo de defini��o: M�dulo lista **********/