#include "../lib/decode.h"
#include "../lib/get_header.h"



huffman_tree* get_huffman_tree(huffman_tree* tree, unsigned char* pre_order, int tree_size, int* counter)
{
    if(*counter >= tree_size) return NULL;

    unsigned char * aux = (unsigned char*) malloc(sizeof(unsigned char));
    if( pre_order[*counter] == '*')
    {
        *aux = '*';
        tree = create_huffman_tree_node(aux,0,NULL, NULL);
        (*counter)++;
        tree->left = get_huffman_tree(tree->left, pre_order, tree_size, counter);
        (*counter)++;
        tree->right = get_huffman_tree(tree->right, pre_order, tree_size, counter);
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