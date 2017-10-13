#include "../lib/encode.h"
#include "../lib/bitmask.h"

int* count_frequency(unsigned char *file_data, int size)
{
    int i;
    int *frequency = (int*)malloc(sizeof(int) * 256);
    memset(frequency, 0, 256 * sizeof(int));
    for(i = 0; i < size; i++)frequency[file_data[i]]++;
    return frequency;
}

huffman_tree* build_huffman_tree(int *frequency)
{
    heap *huffman_heap = create_heap();
    int i;
    huffman_tree *node = NULL, *left = NULL, *right = NULL, *parent = NULL, *root = NULL;
    unsigned char *item_of_node;
    for (i = 0; i < 256; ++i)
    {
        if(frequency[i] != 0)
        {
            item_of_node = (unsigned char*)malloc(sizeof(unsigned char));
            *item_of_node = (unsigned char)i;
            node = create_huffman_tree_node(item_of_node, frequency[i], NULL, NULL);
            enqueue_huffman_heap(huffman_heap,node);
            item_of_node = NULL;
        }
    }
    while(huffman_heap->size > 1)
    {
        left = dequeue_of_huffman_heap(huffman_heap);
        right = dequeue_of_huffman_heap(huffman_heap);

        item_of_node = (unsigned char*)malloc(sizeof(unsigned char));
        *item_of_node = '*';

        parent = create_huffman_tree_node(item_of_node, (left->frequency) + (right->frequency),left, right);
        enqueue_huffman_heap(huffman_heap, parent);

    }
    root = dequeue_of_huffman_heap(huffman_heap);
    return root;

}
void maping_leaves(huffman_tree *root, node **map, node* path)
{
    if(root->left == NULL && root->right == NULL)
    {
        unsigned char index = *((unsigned char*)root->item);//por causo do ponteiro para void
        map[index] = copy_int_list(path);
        return;
    }

    path = add_int_end(path, 0);
    maping_leaves(root->left, map, path);
    path = remove_last_node(path);
    path = add_int_end(path, 1);
    maping_leaves(root->right, map, path);
    path = remove_last_node(path);
}

node* save_pre_order(huffman_tree *root, node *list_pre_order, int* size_of_tree)
{
	if (root != NULL)
	{
		unsigned char item;
		item = *((unsigned char*)(root->item));

		if (root->left == NULL && root->right == NULL && (item == '\\' || item == '*'))
		{
			(*size_of_tree) += 2;
			list_pre_order = add_unsigned_char_end(list_pre_order, '\\');
			list_pre_order = add_unsigned_char_end(list_pre_order, item);
        	list_pre_order = save_pre_order(root->left, list_pre_order, size_of_tree);
        	list_pre_order = save_pre_order(root->right, list_pre_order, size_of_tree);		
		}
		else 
	    {
	    	(*size_of_tree)++;
	    	list_pre_order = add_unsigned_char_end(list_pre_order, item);
	        list_pre_order = save_pre_order(root->left, list_pre_order, size_of_tree);
	        list_pre_order = save_pre_order(root->right, list_pre_order, size_of_tree);
	    }
	}
	
    return list_pre_order;
}

int get_bits_size(node **map, int *frequency)
{
    int i;
    int bits_size = 0;
    int list_size;

    for(i = 0; i<256; i++)
    {
        list_size = 0; 
        
        if(frequency[i] != 0) 
        {
            list_size = list_count(map[i], 0);
            bits_size += list_size * frequency[i];
        } 

    }
    return bits_size;
}

int get_trash_size(int total_bits)
{
    return (8 - (total_bits % 8) ) % 8; 
}
/*
unsigned char* make_header(node* list_pre_order, int trash_size, int size_of_tree)
{
    unsigned char* header = (unsigned char*) malloc((2 + size_of_tree) * sizeof(unsigned char));
    memset(header, 0, (2 + size_of_tree) * sizeof(unsigned char));
    int i;
    for(i = 0; i<)
    {

    }
}
*/