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

void mount_uncompressed_file(FILE* compressed_file, huffman_tree*tree, int trash, int size_tree)
{
	huffman_tree* aux_tree= tree;	
	FILE *uncompressed_file=fopen("uncompressed","wb");
    
	int bit_counter=1, j, size_file;    
	unsigned char byte; 

	if (tree==NULL || compressed_file==NULL)
	{
		printf("ERRO\n");
		return;
	}
	if (aux_tree->left == NULL && aux_tree->right == NULL)
	{
		fprintf(uncompressed_file, "%c", *((unsigned char *)aux_tree->item) ); 
	}
	fseek(compressed_file,0,SEEK_END);
	size_file = ftell(compressed_file) * 8;
	rewind(compressed_file);
	fseek(compressed_file,2+size_tree,SEEK_SET);
	size_tree = size_tree*8;
	size_file = ((size_file-trash)-size_tree) - 16;

	fscanf(compressed_file,"%c",&byte);

    // BUG AQUI!!! ALTERAMOS A CONDIÇÃO DE PARADA DO WHILE 

	while(bit_counter <= size_file) 
	{
		for (j = 7; j >=0 ; --j)
		{
			bit_counter++;
			if (is_bit_i_set(byte,j)) aux_tree=aux_tree->right;
				
			else aux_tree=aux_tree->left;
				
			if (aux_tree->left==NULL && aux_tree->right==NULL)
			{
				fprintf(uncompressed_file,"%c", *((unsigned char *)aux_tree->item) );
				aux_tree=tree;
			}
			if (bit_counter>size_file)
			{
				break;
			}
		}
		fscanf(compressed_file,"%c",&byte);
	}
}