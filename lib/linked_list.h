#ifndef HUFFMAN_LINKED_LIST_H
#define HUFFMAN_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
	Define o tipo abstrato 'node', ponteiro para void e um ponteiro para struct node.
*/
typedef struct node
{
    void *item;
    struct node *next;
}node;

/*
    Inicializa uma lista vazia.
*/
node* create_list();

/*
    Retorna 1 se a lista ta vazia e 0 se não.
*/
int is_list_empty(node* head);

/*
    Adiciona um node, com um inteiro como item, no final da lista. Retorna um ponteiro pro começo da lista.
*/
node* add_int_end(node* head, int item);

/*
    Adiciona um node, com um unsigned char como item, no final da lista. Retorna um ponteiro pro começo da lista.
*/
node* add_unsigned_char_end(node* head, unsigned char item);

/*
    Remove o último node. Retorna um ponteiro pro começo da lista.
*/
node* remove_last_node(node* head);

/*
    Cria uma nova lista igual a lista passada.
*/
node* copy_int_list(node *head);

/*
    Imprime uma lista que possue o inteiros como item.
*/
void print_int_list(node* head);

/*
    Imprime uma lista que possue unsigned char como item.
*/
void print_unsigned_char_list(node* head);

/*
    Conta os elementos da lista e retorna seu tamanho
*/
int list_count(node* head, int size);


#endif //HUFFMAN_LINKED_LIST_H
