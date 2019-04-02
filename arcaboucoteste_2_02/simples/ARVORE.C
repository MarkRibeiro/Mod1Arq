/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include <stdlib.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

		 struct tgNoArvore * pNoCostura ;
               /* Ponteiro para o proximo a ser costurado*/

		 struct NoLista* pNoLista;
				/*Ponteiro para a lista encadeada de inteiros*/
               
               

         char Valor ;
               /* Valor do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;


   /***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do primeiro nó da costura
*
*
*  $ED Descrição do tipo
*     O primeiro no da costura é a primeira folha que vai iniciar o processo de costura.
*
***********************************************************************/

   typedef struct primeiroCostura {
	   tpNoArvore * pNoIni; //Ponteiro para o primeiro nó da costura
	   tpNoArvore * pNoCorr; //Ponteiro para o nó corrente da costura
   } PrimCost;

    /***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da lista de numeros
*
*
*  $ED Descrição do tipo
*     Lista encadeada de inteiros que fara parte das folhas da arvore.
*
***********************************************************************/

   typedef struct noLista  
   { 
	   int chave; 
	   struct noLista * prox; 
   }NoLista; 

/*****  Dados encapsulados no módulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

	  static PrimCost * costura = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {
      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

   /***************************************************************************/

   /*Começo da função Faz Lista*/
   void fazLista(tpNoArvore *No, int n1, int n2, int n3)
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

	   while(No!=NULL)
	   {
		   No->pNoLista=No1;
		   No=No->pNoCostura;
	   }
   }

   ARV_tpCondRet ARV_Faz_Lista( int n1, int n2, int n3 )
   {
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoCorr != NULL )
         {
			 fazLista( costura->pNoIni, n1, n2, n3 ) ;
         } 
		 else
		 {
			 return ARV_CondRetArvoreVazia ;
		 }
		 return ARV_CondRetOK ;
      }
	  else
	  {
		  return ARV_CondRetArvoreNaoExiste ;
	  }

   } /* Fim função: ARV Faz Lista */


   /***************************************************************************/
   /****Função: Costura ****/
   /* Função de troca de posição dos nós 'a' e 'b'*/
   void troca(tpNoArvore *a, tpNoArvore *b) 
   { 
	   tpNoArvore * aux = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;

	   aux->pNoCostura=a->pNoCostura;
	   aux->pNoDir=a->pNoDir;
	   aux->pNoEsq=a->pNoEsq;
	   aux->pNoPai=a->pNoPai;
	   aux->Valor=a->Valor;

	   a->pNoDir=b->pNoDir;
	   a->pNoEsq=b->pNoEsq;
	   a->pNoPai=b->pNoPai;
	   a->Valor=b->Valor;

	   b->pNoDir=aux->pNoDir;
	   b->pNoEsq=aux->pNoEsq;
	   b->pNoPai=aux->pNoPai;
	   b->Valor=aux->Valor;
   } 


   /*Função que recebe a lista de costura e a ordena alfabeticamente*/
   void Ajeita_Lista(tpNoArvore *start) 
   { 
	   int swapped, i; 
	   tpNoArvore *ptr1; 
	   tpNoArvore *lptr = NULL;

	   do
	   { 
		   swapped = 0; 
		   ptr1 = start; 

		   while (ptr1 != lptr) 
		   { 
			   if (ptr1->pNoCostura!=NULL && (ptr1->Valor > ptr1->pNoCostura->Valor)) 
			   {  
				   troca(ptr1, ptr1->pNoCostura); 
				   swapped = 1; 
			   } 
			   ptr1 = ptr1->pNoCostura; 
		   } 
		   lptr = ptr1; 
	   } 
	   while (swapped); 
   } 


   void Costura (tpNoArvore * pNo)
   {
	    if(costura==NULL)
		{
			costura = ( PrimCost * ) malloc( sizeof( PrimCost )) ;
			costura->pNoIni=NULL;
			costura->pNoCorr=NULL;
		}
	   
		if(pNo==NULL)
		{
			return;
		}

		if(pNo->pNoDir!=NULL)
			Costura(pNo->pNoDir);

		if(pNo->pNoEsq!=NULL)
			Costura(pNo->pNoEsq);

		if(pNo->pNoDir==NULL && pNo->pNoEsq==NULL)
		{
			if(costura->pNoIni==NULL)
			{
				costura->pNoIni= pNo;
				costura->pNoCorr= pNo;
			}
			else
			{
				costura->pNoCorr->pNoCostura=pNo;
				costura->pNoCorr=pNo;
			}
		}
   }

   ARV_tpCondRet ARV_Costura( void )
   {
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoCorr != NULL )
         {
            Costura( pArvore->pNoRaiz ) ;
         } 
		 else
		 {
			 return ARV_CondRetArvoreVazia ;
		 }
		 Ajeita_Lista(costura->pNoIni);
		 return ARV_CondRetOK ;
      }
	  else
	  {
		  return ARV_CondRetArvoreNaoExiste ;
	  }

   } /* Fim função: ARV Costura */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************/
  /* *  Função: Printa Testes
*  ****/

   void Print_Testes ()
   {
	   tpNoArvore *No = costura->pNoIni;
	   printf("Costura: ");
	   while(No!=NULL)
	   {
		   printf("%c -> ", No->Valor);
		   No=No->pNoCostura;
	   }
	   No = costura->pNoIni;
	   printf("Lista encadeada de numeros:\n");
	   while (No != NULL) 
	   { 
		   printf("%c : %d->%d->%d\n", No->Valor, No->pNoLista->chave, No->pNoLista->pNoLista->chave, 
										No->pNoLista->pNoLista->pNoLista->chave);
		   No = No->pNoCostura; 
	   } 
   }

      ARV_tpCondRet ARV_Printa( void )
   {
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoCorr != NULL )
         {
            Print_Testes() ;
         } 
		 else
		 {
			 return ARV_CondRetArvoreVazia ;
		 }
		 return ARV_CondRetOK ;
      }
	  else
	  {
		  return ARV_CondRetArvoreNaoExiste ;
	  }

   } /* Fim função: Printa Costura */
/*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->pNoCostura = NULL;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {
      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;
      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/

