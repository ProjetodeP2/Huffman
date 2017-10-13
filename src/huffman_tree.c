#include "../lib/huffman_tree.h"


huffman_tree* create_leaf(void *item, int frequency)
{
	huffman_tree* new_leaf = (huffman_tree*) malloc(sizeof(huffman_tree));

	new_leaf->item = item;
	new_leaf->frequency = frequency;
	new_leaf->left = NULL;
	new_leaf->right = NULL;

	return new_leaf;
}

huffman_tree* create_parent(huffman_tree* left, huffman_tree* right)
{
	huffman_tree* new_parent = malloc(sizeof(huffman_tree));

	unsigned char *parent_item = NULL;
	parent_item = (unsigned char*)malloc(sizeof(unsigned char));
	*parent_item = '*';

	new_parent->item = parent_item;
	new_parent->left = left;
	new_parent->right = right;
	new_parent->frequency = left->frequency + right->frequency;

	return new_parent;
}

huffman_tree* search(huffman_tree* huffman, unsigned char item)
{
	huffman_tree* found = NULL;

	if(huffman == NULL) return NULL;

	if(*((unsigned char*)huffman->item) == item) return huffman;
	else
	{
		if(huffman->left != NULL) result = search(huffman->left,item);
		if(found == NULL && huffman->right != NULL) found = search(huffman->right,item);
	}
	return found;
}

int max (int x, int y)
{
	return (x > y) ? x:y;
}

int height (huffman_tree* huffman_tree)
{
	if (huffman_tree == NULL) return -1;
	else return (1 + max(height(huffman_tree->left), height(huffman_tree->right)));
}

void print_unsigned_char_in_order(huffman_tree *ht)
{
    if (ht != NULL)
    {
        print_unsigned_char_in_order(ht->left);
        printf("%c ",*((unsigned char*)ht->item));
        print_unsigned_char_in_order(ht->right);
    }
}
