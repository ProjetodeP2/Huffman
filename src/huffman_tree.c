#include "../lib/huffman_tree.h"


huffman_tree* create_leaf(unsigned char item, int frequency)
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

	new_parent->item = '*';
	new_parent->left = left;
	new_parent->right = right;
	new_parent->frequency = left->frequency + right->frequency;

	return new_parent;
}

huffman_tree* search(huffman_tree* huffman, unsigned char item)
{
	huffman_tree* found = NULL;

	if(huffman == NULL) return NULL;

	if(huffman->item == item) return huffman;
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


huffman_tree* build_huffman_tree(int* frequency)
{
	int i;
	huffman_tree* leaf;
	huffman_tree* root;
	huffman_tree* right;
	huffman_tree* left;
	huffman_tree* parent;

	heap* heap = create_heap();

	for(i = 0; i < 256; i++)
	{
		if(frequency[i] != 0)
		{
			leaf = create_leaf(i, frequency[i]);
			enqueue(heap, leaf);
		}
	}
	while(heap->size > 1 )
	{
		left   = dequeue(heap);
		right  = dequeue(heap);
		parent = create_parent(left, right);
		enqueue(heap, parent);
	}
	root = dequeue(heap);
	return root;
}