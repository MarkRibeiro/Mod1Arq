/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Lista
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
		3.00   avs   02/04/2019 Ajustes finais para a unifica��o com os outros m�dulos
*       2.00   avs   01/04/2019 Unifica��o com os outros m�dulos
*       1.00   avs   29/03/2019 In�cio do desenvolvimento
*
***************************************************************************/

#include "ARVORE.H"

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da lista de numeros
*
*
*  $ED Descri��o do tipo
*     Lista encadeada de inteiros que fara parte das folhas da arvore.
*
***********************************************************************/

   struct noLista  
   { 
	   int chave; 
	   struct noLista * prox; 
   }; 

/*Come�o da fun��o que cria a lista*/
   NoLista* LIS_Cria(int n1, int n2, int n3)
   {
	   NoLista*No1,*No2,*No3;
	   No1=(NoLista*)malloc(sizeof(NoLista));
	   No2=(NoLista*)malloc(sizeof(NoLista));
	   No3=(NoLista*)malloc(sizeof(NoLista));

	   No1->chave=n1;
	   No2->chave=n2;
	   No3->chave=n3;

	   No1->prox=No2;
	   No2->prox=No3;
	   No3->prox=NULL;

	   return  No1;
   }
   //Fim da fun��o que cria a lista

   /***********************************************************************/

   //Come�o da fun��o que printa a lista
   void LIS_Printa(NoLista* No)
   {
	   printf("%d->%d->%d\n", No->chave,No->prox->chave,No->prox->prox->chave);
   }
   //Fim da fun��o que printa a lista

   /********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/