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
    while(get_heap_size(huffman_heap) > 1)
    {
        left = dequeue_of_huffman_heap(huffman_heap);
        right = dequeue_of_huffman_heap(huffman_heap);

        item_of_node = (unsigned char*)malloc(sizeof(unsigned char));
        *item_of_node = '*';

        parent = create_huffman_tree_node(item_of_node, get_huffman_node_frequency(left) + get_huffman_node_frequency(right),left, right);
        enqueue_huffman_heap(huffman_heap, parent);

    }
    root = dequeue_of_huffman_heap(huffman_heap);
    return root;

}
void maping_leaves(huffman_tree *root, node **map, node* path)
{
    if(get_left_huffman_node(root) == NULL && get_right_huffman_node(root) == NULL)
    {
        unsigned char index = *((unsigned char*)get_huffman_node_item(root));
        map[index] = copy_int_list(path);
        return;
    }

    path = add_int_list_end(path, 0);
    maping_leaves(get_left_huffman_node(root), map, path);
    path = remove_last_list_node(path);
    path = add_int_list_end(path, 1);
    maping_leaves(get_right_huffman_node(root), map, path);
    path = remove_last_list_node(path);
}

node* save_pre_order(huffman_tree *root, node *list_pre_order, int* size_of_tree)
{
    if (root != NULL)
    {
        unsigned char item;
        item = *((unsigned char*)get_huffman_node_item(root));

        if (get_left_huffman_node(root) == NULL && get_right_huffman_node(root) == NULL && (item == '\\' || item == '*'))
        {
            (*size_of_tree) += 2;
            list_pre_order = add_unsigned_char_list_end(list_pre_order, '\\');
            list_pre_order = add_unsigned_char_list_end(list_pre_order, item);
            list_pre_order = save_pre_order(get_left_huffman_node(root), list_pre_order, size_of_tree);
            list_pre_order = save_pre_order(get_right_huffman_node(root), list_pre_order, size_of_tree);
        }
        else
        {
            (*size_of_tree)++;
            list_pre_order = add_unsigned_char_list_end(list_pre_order, item);
            list_pre_order = save_pre_order(get_left_huffman_node(root), list_pre_order, size_of_tree);
            list_pre_order = save_pre_order(get_right_huffman_node(root), list_pre_order, size_of_tree);
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

int* decimal_to_binary(int decimal, int max)
{
    int count = 0;
    int temporary[max];
    memset(temporary, 0, max * sizeof(int));
    while(decimal)
    {
        temporary[count++] = (decimal % 2);
        decimal = decimal/2;
    }
    int *final = (int*)malloc(max * sizeof(int));
    memset(final, 0, max * sizeof(int));
    int i, j;
    for (i = 0, j = max - 1; i < max; ++i)
    {
        final[i] = temporary[j - i];
    }

    return final;
}

unsigned char* make_header(node* list_pre_order, int trash_size, int size_of_tree)
{
    unsigned char* header = (unsigned char*) malloc((2 + size_of_tree) * sizeof(unsigned char));
    memset(header, 0, (2 + size_of_tree) * sizeof(unsigned char));
    int *trash_size_binary = decimal_to_binary(trash_size, 3);
    int *tree_size_binary = decimal_to_binary(size_of_tree, 13);


    int i, bit_counter, byte_index, array_index;

    for (bit_counter = 15, byte_index = 0, array_index = 0; bit_counter >= 0 ; --bit_counter, ++array_index)
    {
        if(bit_counter == 7)byte_index = 1;
        if(bit_counter == 12)array_index = 0;
        if(bit_counter >= 13)
        {
            if(trash_size_binary[array_index])
            {
                header[byte_index] = set_bit(header[byte_index], bit_counter%8);
            }

        }
        else
        {
            if(tree_size_binary[array_index])
            {
                header[byte_index] = set_bit(header[byte_index], bit_counter%8);
            }
        }
    }
    node *aux = list_pre_order;
    for ( i = 0; i < size_of_tree; ++i)
    {
        header[i+2] = *((unsigned char*)get_linked_list_item(aux));
        aux = get_linked_list_next_node(aux);
    }

    return header;

}


unsigned char* make_file_content(unsigned char *file_data, int file_size, node **map, int total_amount_of_bytes)
{
    int i;
    int current_bit = 7, current_byte = 0;
    node *path = NULL;
    unsigned char *compacted_file_content = (unsigned char*)malloc(total_amount_of_bytes * sizeof(unsigned char));
    memset(compacted_file_content, 0, total_amount_of_bytes* sizeof(unsigned char));
    for (i = 0; i < file_size; ++i)
    {
        path = map[file_data[i]];
        while(path != NULL)
        {
            if(*(int *)get_linked_list_item(path))
            {
                compacted_file_content[current_byte] = set_bit(compacted_file_content[current_byte], current_bit);
            }
            path = get_linked_list_next_node(path);
            --current_bit;
            if(current_bit < 0)
            {
                ++current_byte;
                current_bit = 7;
            }
        }
    }
    return compacted_file_content;
}

void create_final_file(unsigned char *header, unsigned char *compacted_file_content, int tree_size, int total_amount_of_bytes)
{
    FILE *final_file;
    final_file =  fopen("compacted.huff", "wb");

    fwrite(header , sizeof(unsigned char), tree_size+2, final_file);
    fwrite(compacted_file_content , sizeof(unsigned char), total_amount_of_bytes, final_file);
    fclose(final_file);

}

