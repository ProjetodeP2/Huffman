#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Define o tipo abstrato 'huffman_tree', cujo a struct contém um ponteiro para void para armazenar qualquer tipo deitem, a frequência do nó no arquivo,
    um ponteiro para o nó filho da esquerda e um ponteiro para o nó filho da direita.
*/

typedef struct huffman_tree huffman_tree;
/*
    Retorna um ponteiro para huffman_tree com o nó à esquerda do 'root'.
*/
huffman_tree* get_left_huffman_node(huffman_tree *root);
/*
    Retorna um ponteiro para huffman_tree com o nó à direita do 'root'.
*/
huffman_tree* get_right_huffman_node(huffman_tree *root);
/*
    Retorna um inteiro com a frequência do nó 'root'.
*/
int get_huffman_node_frequency(huffman_tree *root);
/*
    Retorna um ponteiro para void que aponta para o item de 'root'.
*/
void* get_huffman_node_item(huffman_tree *root);
/*
    Define 'left' como o nó à esquerda do nó 'root'.
*/
void set_left_huffman_node(huffman_tree *root, huffman_tree *left);
/*
    Define 'right' como o nó à direita do nó 'root'.
*/
void set_right_huffman_node(huffman_tree *root, huffman_tree *right);

/*
    Cria um nó com o item, a frequência e seus filhos à esquerda e direita. Retorna um ponteiro para o mesmo
*/
huffman_tree* create_huffman_tree_node(void *item, int frequency, huffman_tree *left, huffman_tree *right);

/*
    Troca o conteúdo entre dois nós da árvore de huffman
*/
void huffman_tree_swap(huffman_tree *a, huffman_tree *b);

/*
    Imprime a arvore de huffman, que armazena unsigned chars, em in-order
*/
void print_unsigned_char_pre_order(huffman_tree *ht);

#endif //HUFFMAN_HUFFMAN_TREE_H
