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
        int *frequency = count_frequency(file_data, file_size);
        //now we neesd to build our huffman tree
        huffman_tree *root = build_huffman_tree(frequency);
        //apartir daqui é tudo temporario
        //precisamos agora mapear a arvore
        printf("Pre ordem da arvore: ");
        print_unsigned_char_pre_order(root);
        printf("\n");
        node *map[256];
        int i;
       for (i = 0; i < 256; ++i)
       {
            map[i] = NULL;
       }
       maping_leaves(root, map, NULL);

        node *list_pre_order = create_list();
        int size_of_tree = 0;
        list_pre_order = save_pre_order(root, list_pre_order, &size_of_tree);

        //print_unsigned_char_list(list_pre_order);
        //printf("Tamanho da Arvore: %d\n", size_of_tree);

       int total_amount_of_bits, trash_size;
        total_amount_of_bits = get_bits_size(map, frequency);
        
        //printf("Amount of bytes: %d\n", total_amount_of_bits);


        //printf("Qnt total de bits: %d\n", total_amount_of_bits);
        trash_size = get_trash_size(total_amount_of_bits);
        //printf("Tamanho do lixo: %d\n", trash_size);
       

        unsigned char *header = make_header(list_pre_order, trash_size, size_of_tree);
        int j;
        /*for (i = 15, j = 0; i >= 0 ; --i)
        {
            if(i==7)j=1;
            printf("%d ", is_bit_i_set(header[j], i%8));
        }
        printf("\n");
      /*
        printf("HEADER: \n");
        for (i = 0; i <= 2 + size_of_tree; ++i)
        {
            printf("%c ", header[i]);
        }
      */
       printf("\n");
      
        //NEW

        int total_amount_of_bytes = (int) ceil(total_amount_of_bits/8.0);
        unsigned char *compacted_file_content = make_file_content(file_data, file_size, map, total_amount_of_bytes);
        create_final_file(header, compacted_file_content, size_of_tree, total_amount_of_bytes);

    }
}

void decoding(FILE* file)
{
    int trash_size, tree_size;
    int i;
    trash_size = trash(file);
    tree_size  = get_tree_size(file);

    
    unsigned char * pre_order = (unsigned char*)malloc(tree_size * sizeof(unsigned char));
    pre_order = pre_order_tree(file, tree_size);

    /*
    printf("Trash_size: %d\n", trash_size);
    printf("Tree Size: %d\n",  tree_size);

    printf("Pre order tree: ");
    
    for(i = 0; i < tree_size; i++){
        printf("%c", pre_order[i]);
    }
    printf("\n");
    */
    int counter = 0;
    huffman_tree* tree = NULL;
    tree = get_huffman_tree(tree, pre_order, tree_size, &counter);
    printf("Arvore remontada: ");
    print_unsigned_char_pre_order(tree);

}






int main() {

    char url[10000];
    
    printf("Digite a url do arquivo: \n");
    scanf("%s", url);
    FILE *file;

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
