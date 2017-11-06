#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"
#include "huffman_heap.h"
#include "huffman_tree.h"
#include "bitmask.h"
#include "get_header.h"

/*
    Recupera a árvore de huffman a partir da pré ordem
*/
huffman_tree* get_huffman_tree(huffman_tree* tree, unsigned char* pre_order, int tree_size, int* counter);

/*
    Recebe o arquivo comprimido, a árvore de huffman, o tamanho do lixo e o tamanho da árvore e cria o arquivo final descomprimido
*/
void mount_uncompressed_file(FILE* compressed_file, huffman_tree*tree, int trash, int size_tree);

#endif //HUFFMAN_DECODE_H
