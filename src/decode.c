#include "../lib/decode.h"

huffman_tree* get_huffman_tree(huffman_tree* tree, unsigned char* pre_order, int tree_size, int* counter)
{
    if(*counter >= tree_size) return NULL;

    unsigned char * aux = (unsigned char*) malloc(sizeof(unsigned char));
    if( pre_order[*counter] == '*')
    {
        *aux = '*';
        tree = create_huffman_tree_node(aux,0,NULL, NULL);
        (*counter)++;
        set_left_huffman_node(tree, get_huffman_tree(get_left_huffman_node(tree), pre_order, tree_size, counter));
        (*counter)++;
        set_right_huffman_node(tree, get_huffman_tree(get_right_huffman_node(tree), pre_order, tree_size, counter));
    }
    else
    {
        if(pre_order[*counter] == '\\')
        {
            (*counter)++;
            *aux = pre_order[*counter];
            tree = create_huffman_tree_node(aux,0,NULL, NULL);
        }
        else
        {
            *aux = pre_order[*counter];
            tree = create_huffman_tree_node(aux,0,NULL, NULL);
        }
    }

    return tree;
}


void mount_uncompressed_file(FILE* compressed_file, huffman_tree*tree, int trash, int size_tree)
{
    huffman_tree* aux_tree = tree;
    FILE *uncompressed_file = fopen("uncompressed","wb");

    int bit_counter = 1, j, file_size_bits, tree_size_bits;
    unsigned char byte;

    if (tree == NULL || compressed_file == NULL)
    {
        printf("ERROR\n");
        return;
    }

    fseek(compressed_file,0,SEEK_END);
    file_size_bits = (ftell(compressed_file) * 8);
    rewind(compressed_file);
    fseek(compressed_file,2 + size_tree,SEEK_SET);
    tree_size_bits = (size_tree * 8); 
    file_size_bits = (((file_size_bits - trash) - tree_size_bits) - 16);

    fscanf(compressed_file,"%c",&byte);

    while(bit_counter <= file_size_bits)
    {
        for (j = 7; j >=0 ; --j)
        {
            bit_counter++;
            if (is_bit_i_set(byte,j)) aux_tree = get_right_huffman_node(aux_tree);

            else aux_tree = get_left_huffman_node(aux_tree);

            if (get_left_huffman_node(aux_tree) == NULL && get_right_huffman_node(aux_tree) == NULL)
            {
                fprintf(uncompressed_file,"%c", *((unsigned char *)get_huffman_node_item(aux_tree)));
                aux_tree = tree;
            }
            if (bit_counter > file_size_bits)
            {
                break;
            }
        }
        fscanf(compressed_file,"%c",&byte);
    }

    fclose(uncompressed_file);
}
