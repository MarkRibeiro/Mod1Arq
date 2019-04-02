#include<stdio.h> 
#include<stdlib.h> 
  
typedef struct no  
{ 
  int chave; 
  struct no *prox; 
}No; 

void printList(No *n) 
{ 
  while (n != NULL) 
  { 
     printf("%d->", n->chave); 
     n = n->prox; 
  } 
  printf("NULL\n"); 
} 

void fazLista(No *cab, int n)
{
	No* novo;
	novo  = (No*)malloc(sizeof(No));

	if( cab->prox == NULL )
	{
		if(cab->chave == NULL)
		{
			cab->chave = n;
		}

		else
		{
			cab->prox = novo;
			novo->prox = NULL;
			novo->chave = n;
		}
		 return;
	}

	else
		fazLista(cab->prox, n);
}
  
int main() 
{ 
  No* head  = (No*)malloc(sizeof(No));
  head->prox = NULL;
  head->chave = NULL;
  
  fazLista(head, 1);
  fazLista(head, 2);
  fazLista(head, 3);
  fazLista(head, 4);
  fazLista(head, 5);
  fazLista(head, 6);
  fazLista(head, 7);
  fazLista(head, 8);
  fazLista(head, 9);
  
  printList(head); 
   
  return 0; 
}