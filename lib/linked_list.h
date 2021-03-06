#ifndef HUFFMAN_LINKED_LIST_H
#define HUFFMAN_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
    Define o tipo abstrato 'node', ponteiro para void e um ponteiro para struct node.
*/
typedef struct node node;

/*
    Retorna um ponteiro para void que apnta para o item de 'head'.
*/
void* get_linked_list_item(node *head);
/*
    Retorna um ponteiro para node com o prómixo nó da lista encadeada.
*/
node* get_linked_list_next_node(node *head);

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
node* add_int_list_end(node* head, int item);

/*
    Adiciona um node, com um unsigned char como item, no final da lista. Retorna um ponteiro pro começo da lista.
*/
node* add_unsigned_char_list_end(node* head, unsigned char item);

/*
    Remove o último node. Retorna um ponteiro pro começo da lista.
*/
node* remove_last_list_node(node* head);

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