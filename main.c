#include "lib/encode.h"

void encoding(FILE *file)
{
    //we need to find the size of the file
    int file_size, amount_of_bytes;
    fseek(file,0, SEEK_END);
    file_size = ftell(file);
    //this string will receive the file data
    unsigned char file_data[file_size];
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
        print_unsigned_char_in_order(root);
        printf("\n");
        node *map[256];
        int i;
        for (i = 0; i < 256; ++i)
        {
            map[i] = NULL;
        }
        maping_leaves(root, map, NULL);
        
        
        print_int_list(map['A']);
        print_int_list(map['B']);
        print_int_list(map['C']);
        print_int_list(map['D']);
        print_int_list(map['E']);
        print_int_list(map['F']);
        
        node *list_pre_order = create_list();
        int size_of_tree = 0;

        list_pre_order = save_pre_order(root, list_pre_order, &size_of_tree);
        printf("\n\n");
        print_unsigned_char_list(list_pre_order);
        printf("Tamanho da Arvore: %d\n", size_of_tree);
    }
}

int main() {
    char url[] = "test.txt";
    FILE *file;
    file =  fopen(url, "rb");
    if (file == NULL) {
        printf("Failed to load the file\n\n");
    } else {
        encoding(file);
    }
    return 0;
}
