#ifndef HUFFMAN_LINKED_LIST_H
#define HUFFMAN_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    int item;
    struct node *next;
}node;

//inicializa uma lista vazia
node* create_list();
//returna 1 se a lista ta vazia e 0 se não.
int is_list_empty(node* head);

//adciona um node no final da lista
node* add_end(node* head, int item);
//remove o último node
node* remove_last_node(node* head);

node* copy_list(node *head);

void print_list(node* head);




#endif //HUFFMAN_LINKED_LIST_H
