
#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huffman_tree
{
    void *item;
    int frequency;
    struct huffman_tree *left;
    struct huffman_tree *right;
}huffman_tree;

huffman_tree* create_huffman_tree_node(void *item, int frequency, huffman_tree *left, huffman_tree *right);

void huffman_tree_swap(huffman_tree *a, huffman_tree *b);

void print_unsigned_char_in_order(huffman_tree *ht);

#endif //HUFFMAN_HUFFMAN_TREE_H
