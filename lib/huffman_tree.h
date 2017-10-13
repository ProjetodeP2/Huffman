#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <stdio.h >
#include <stdlib.h>
#include <string.h> 

typedef struct huffman_tree
{
	int frequency;
	void* item;
	struct huffman_tree* left;
	struct huffman_tree* right;
} huffman_tree;

/*
    Recebe o item e sua frequência no arquivo e cria um nó filho.
*/
huffman_tree* create_leaf(unsigned char item, int frequency);

/*
    Recebe os dois nós de menor frequência da heap, e cria um pai "*" cuja frequência é a soma dos dois nós.
*/
huffman_tree* create_parent(huffman_tree* left, huffman_tree* right);

huffman_tree* search(huffman_tree* huffman, unsigned char item);

int max (int x, int y);

int height (huffman_tree* huffman_tree);

/* 

*/
huffman_tree* build_huffman_tree(int* frequency);

void print_unsigned_char_in_order(huffman_tree *ht);


#endif //HUFFMAN_HUFFMAN_TREE_H
