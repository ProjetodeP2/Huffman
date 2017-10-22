#include "../lib/huffman_tree.h"

huffman_tree* create_huffman_tree_node(void *item, int frequency, huffman_tree *left, huffman_tree *right)
{
    huffman_tree *node = (huffman_tree*)malloc(sizeof(huffman_tree));
    node->item = item;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

void huffman_tree_swap(huffman_tree *a, huffman_tree *b)
{
    huffman_tree aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
void print_unsigned_char_pre_order(huffman_tree *ht)
{
    if (ht != NULL)
    {
        printf("%c ",*((unsigned char*)ht->item));
        print_unsigned_char_pre_order(ht->left);
        print_unsigned_char_pre_order(ht->right);
    }
}