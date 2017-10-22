#include "lib/encode.h"
#include "lib/decode.h"
#include "lib/get_header.h"

void encoding(FILE *file)
{
    //we need to find the size of the file
    int file_size, amount_of_bytes;
    fseek(file,0, SEEK_END);
    file_size = ftell(file);
    
    //this string will receive the file data
 	//ALERTA!!!! AQUI Q ESTAVA O BUG
    unsigned char *file_data = (unsigned char*)malloc(file_size * sizeof(unsigned char));
    rewind(file);
    //transfer the file data to the string
    amount_of_bytes = (int) fread(file_data, 1, (size_t)file_size, file);
    if(amount_of_bytes != file_size)
    {
        printf("Failed to transfer the file data to the string");
        return;
    }
    else
    {
        //we need to count the frequency of which byte of the string
        int i, j;
        int *frequency = count_frequency(file_data, file_size);

        printf("Building Huffman tree................\n");
        huffman_tree *root = build_huffman_tree(frequency);
        printf("Huffman Tree successfully built!\n\n");
        
        node *map[256];
        
        for (i = 0; i < 256; ++i)
        {
             map[i] = NULL;
        }
       
        printf("Maping leaves................\n");
        maping_leaves(root, map, NULL);
        printf("Maping successfully done!\n\n");


        printf("Making Header..................\n");
        node *list_pre_order = create_list();
        int size_of_tree = 0;
        list_pre_order = save_pre_order(root, list_pre_order, &size_of_tree);
        int total_amount_of_bits, trash_size;
        total_amount_of_bits = get_bits_size(map, frequency);
        trash_size = get_trash_size(total_amount_of_bits);
        unsigned char *header = make_header(list_pre_order, trash_size, size_of_tree);
        printf("Header successfully made!\n\n");
        

        int total_amount_of_bytes = (int) ceil(total_amount_of_bits/8.0);
        unsigned char *compacted_file_content = make_file_content(file_data, file_size, map, total_amount_of_bytes);
        printf("Creating compressed file..................\n");
        create_final_file(header, compacted_file_content, size_of_tree, total_amount_of_bytes);
        printf("File successfully compressed!\n\n");
    }
}

void decoding(FILE* file)
{
    int i, trash_size, tree_size;
    int counter = 0;
    
    printf("Retrieving Header........................\n");
    trash_size = trash(file);
    tree_size  = get_tree_size(file);

    unsigned char * pre_order = (unsigned char*)malloc(tree_size * sizeof(unsigned char));
    pre_order = pre_order_tree(file, tree_size);
    printf("Header successfully retrieved!\n\n");

    huffman_tree* tree = NULL;
    printf("Retrieving Huffman tree........................\n");
    tree = get_huffman_tree(tree, pre_order, tree_size, &counter);
    printf("Huffman tree successfully retrieved!\n\n");
    
    printf("Creating decompressed file........................\n");
    mount_uncompressed_file(file, tree, trash_size,tree_size);
    printf("File successfully decompressed!\n\n");
}

int main() {

    char url[10000];
    
    printf("Digite a url do arquivo: \n");
    scanf("%s", url);
    FILE *file;
    printf("\n");
    file =  fopen(url, "rb");
     if (file == NULL)
     {
        printf("Failed to load the file\n\n");
     }
     else
     {
        if(strstr(url,".huff") == NULL)
        {
            encoding(file);
        }
        else{
            decoding(file);
        }
     }
    return 0;
}
