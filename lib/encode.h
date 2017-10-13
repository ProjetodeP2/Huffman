#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include "huffman_heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "huffman_tree.h"


//Dado uma string com todos os elementos do arquivo e seu tamanho, retorna um array com a frequência dos mesmos.
int* count_frequency(unsigned char *file_data, int size);

/*
 Dado o array com a frequência dos elementos, retorna a árvore de huffman montada.
  Utilizamos uma min_heap como uma fila de prioridade para a menor frequência.
 */
huffman_tree* build_huffman_tree(int *frequency);

/*
Dado uma árvore huffman, um array de ponteiros para node e uma lista, mapeamos o caminho de cada folha da árvore e armazena no array.
*/
void maping_leaves(huffman_tree *root, node **map, node* path);

/*
Dado uma árvore de huffman, salva a sua pre-order em um lista encadeada e guarda seu tamanho.
*/
node* save_pre_order(huffman_tree *root, node *list_pre_order, int* size_of_tree);

/*

*/
int get_bits_size(node **map, int *frequency);

/*

*/
int get_trash_size(int total_bits);

/*

*/
unsigned char* make_header(node* list_pre_order, int trash_size, int size_of_tree);

#endif //HUFFMAN_ENCODE_H
