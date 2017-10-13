#include "../lib/encode.h"

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
//temporario
void maping_leaves(huffman_tree *root, node **map, node* path)
{
    if(root->left == NULL && root->right == NULL)
    {
        unsigned char index = *((unsigned char*)root->item);//por causo do ponteiro para void
        map[index] = copy_list(path);
        return;
    }

    path = add_end(path, 0);
    maping_leaves(root->left, map, path);
    path = remove_last_node(path);
    path = add_end(path, 1);
    maping_leaves(root->right, map, path);
    path = remove_last_node(path);
}

