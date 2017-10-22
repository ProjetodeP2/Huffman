
#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	Define o tipo abstrato 'huffman_tree', cujo a struct contém um ponteiro para void para armazenar qualquer tipo deitem, a frequência do nó no arquivo,
	um ponteiro para o nó filho da esquerda e um ponteiro para o nó filho da direita.
*/
typedef struct huffman_tree
{
    void *item;
    int frequency;
    struct huffman_tree *left;
    struct huffman_tree *right;
}huffman_tree;

//Cria um nó com o item, a frequência e seus filhos a esquerda e direita. Retorna um ponteiro para o mesmo
huffman_tree* create_huffman_tree_node(void *item, int frequency, huffman_tree *left, huffman_tree *right);

//Troca o conteúdo entre dois nós da árvore de huffman
void huffman_tree_swap(huffman_tree *a, huffman_tree *b);
//Imprime a arvore de huffman, que armazena unsigned chars, em in-order
void print_unsigned_char_pre_order(huffman_tree *ht);

#endif //HUFFMAN_HUFFMAN_TREE_H
