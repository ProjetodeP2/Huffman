#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include "huffman_heap.h"
#include "huffman_tree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Dado uma string com todos os elementos do arquivo e seu tamanho, retorna um array com a frequência dos mesmos.
int* count_frequency(unsigned char *file_data, int size);

/*
 Dado o array com a frequência dos elementos, retorna a árvore de huffman montada.
  Utilizamos uma min_heap como uma fila de prioridade para a menor frequência.
 */
huffman_tree* build_huffman_tree(int *frequency);

void maping_leaves(huffman_tree *root, node **map, node* path);

#endif //HUFFMAN_ENCODE_H
