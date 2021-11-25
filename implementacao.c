#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 10

typedef struct NODE {
	int item; 
	struct NODE *next; 
} NODE;

int getHash(int key) {
	return key % TAM_MAX;
}

NODE* getNode() {
    NODE *node = (NODE *) malloc(sizeof(NODE));

    if(node == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    } 

    return node;
}

int findList(int key, NODE **HASH) {
	int index = getHash(key);
	NODE *list = HASH[index];
	while (list != NULL) {
		if (key == list->item) return 1; // Se encontrou retorna verdadeiro
		list = list->next;
	}
	return 0;
}

void init(NODE **HASH) {
	int i;
	for(i=0; i<TAM_MAX; i++)
		 HASH[i]=NULL;		 
}

void insertList(int item, NODE **HASH) {
	int index = getHash(item);
	NODE **list = &HASH[index];
	
	if (*list == NULL) {
		*list = getNode();
  		(*list)->item=item;
  		(*list)->next=NULL;
  		
  		printf("Sucesso: Inserido na posicao %d.\n",index);
 	}
	else { // Se ocorreu colisao
		printf("Atencao: Colisao  na posicao %d.\n",index);
	
	    NODE *temp= HASH[index]; // tempndo indexicao inicial ponteiro
	
		while ((*list)->next != NULL) 
		// Caminha para fim da list caso contenha mais de 2 itens
			*list=(*list)->next; 

      (*list)->next = getNode();
				
		*list=(*list)->next;
  		(*list)->item=item;
  		(*list)->next=NULL; 
  		
  		HASH[index]=temp; // retornando ponteiro para a indexiçao inicial
	}
}

void insert(int item, NODE **HASH) {
	
	int index = getHash(item); // CALCULA indexIÇAO
	
	if (HASH[index]!=NULL) { // se ocorreu colisao
		if (findList(item,HASH)) { // verificando se a key ja existe
			printf("Atencao: O Valor %d ja foi cadastrado.\n",item);
			return;
		}
	}
	
	insertList(item,HASH);
}


void showList(int index, NODE **HASH) { // Percorre list imprimindo-a
	NODE *list = HASH[index];
	while (list != NULL) {
		printf(" %d",list->item);
		list = list->next;
	}
	printf(" NULL");
} 

void showTable(NODE **HASH) { // showTable tabela HASH
	int i;
	printf("Tabela Hash: \n");
	for (i=0; i<TAM_MAX; i++) {
		printf("\nHash[%d] =",i);
		showList(i,HASH);
	}
}


void clear(NODE **HASH) {
	int i;
	NODE *next;
	for(i=0; i<TAM_MAX; i++) {
		NODE **list=&HASH[i]; 
		while(*list!= NULL) { // clearndo list da memoria
  			next = (*list)->next;                
  			free(*list);
  			*list = next; 
  		} 
  	}
  	free(next);  	
}

void remove(int key, NODE **HASH) { 
 int index = getHash(key);
 if (!findList(key,HASH)) { // verificando se item pertence a tabela
 	puts("\nItem nao encontrado");
	return;
 }
	
 NODE **list = &HASH[index];
 NODE *prev = *list;
 NODE *next = (*list)->next;
 NODE *temp = HASH[index]; // tempndo indexicao do ponteiro 

 while (*list!=NULL) { // laço percorre list		
	if ((*list)->item == key) { // Se encontrou o item		
		if (*list == prev) { // Se o item esta NODE inicio
			if ((*list)->next==NULL) { // Se a list indexsui um unico item
				free(*list);
				HASH[index]=NULL;
			}
			else { 
				(*list)->next=next->next;
				(*list)->item=next->item;
				HASH[index]=temp;
			}
		}
		else { // Se o item NAO esta NODE inicio
			prev->next=next;
			free(*list);
			HASH[index]=temp;
		}
		return;
 	} // fim laço encontrou o item		
	prev = *list;
	*list = (*list)->next;
	next = (*list)->next; 		
 } // fim laço percorre list
	
 HASH[index]=temp; // retonando ponteiro para indexicao inicial
 free(prev);
 free(next);
 free(temp);	
}

int main() {
	NODE *HASH[TAM_MAX]; // criando tabela hash (vetor de ponteiros para list)
	init(HASH); // inicializando tabela hash na memoria
	int i;
	int item;
	
    printf("\n----------------------\n");
	printf("Tabela HASH - Encadeamento - %d indexicoes", TAM_MAX);
	printf("\n----------------------");
	printf("\nInserindo 15 elementos");
	for (i=0; i<15; i++){
		printf("\nInserindo elemento %d",i+1);
		printf(" - Forneca valor real: "); 
		scanf("%d",&item);
		insert(item,HASH);
	} 
	
	showTable(HASH);  
	
	do {
		printf("\n\nForneca o item que deseja remover (-1 para sair): ");
		scanf("%d",&item);
		if (item==-1) break;
		remove(item,HASH);	
		showTable(HASH);
	} while(item != -1); 
	
	clear(HASH);
	
	puts("\n");
   return 0;
}
