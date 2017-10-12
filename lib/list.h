#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	void *item;
	struct node *next;
}node;

/*Retorna um ponteiro do tipo node apontando para NULL*/
node* create_empty_list()

/*Adiciona o item no fim da Lista Encadeada e retorna um ponteiro para o início da Lista Encadeada*/
node* add_tail(node* head, void* item)

/*	
	Retorna NULL se a lista encadeada estiver vazia e imprime -1
	Retorna NULL se a lista encadeada contém apenas um item e imprime o item removido
	Remove o último item da lista encadeada, imprime o item removido e retorna um ponteiro 
	para o início da lista encadeada
*/
node* remove_last(node *head, node *previous, node *current)

/*Imprime um lista encadeada de unsigned chars*/
void print(node* head)

/*Recebe uma lista encadeada e copia seu conteúdo para uma segunda lista encadeada retornado um ponteiro para a segunda lista encadeada*/
node* copy_list(node* list1, node* list2);

#endif //LIST_H

