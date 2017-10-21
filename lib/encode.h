#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"
#include "huffman_heap.h"
#include "huffman_tree.h"
#include "bitmask.h"

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
Dado o array de ponteiros para node com os caminhos para as folhas da árvore e o array com a frequência de cada Byte, retornamos um inteiro com a quantidade de bits que teremos no nosso arquivo compactado, excetuando o cabeçalho.
*/
int get_bits_size(node **map, int *frequency);

/*
Dado o número de bits que vai ser posto no arquivo compactado, excetuando o cabeçalho, retorna um inteiro com tamanho do lixo.
*/
int get_trash_size(int total_bits);

/*
Dado um inteiro com valor desejado e outro inteiro com o tamanho do array desejado, retorna o valor 'decimal' como binário em um array de inteiros de tamanho 'max'.
*/
int* decimal_to_binary(int decimal, int max);
/*
    Dado uma lista encadeada com a pré-ordem da árvore de huffman, o tamanho do lixo e o tamanho da árvore, retorna uma string com o cabeçalho do arquivo a ser comprimido.
*/
unsigned char* make_header(node* list_pre_order, int trash_size, int size_of_tree);

/*
    Dado um array com os os bytes do arquivo a ser compactado, o tamanho desse arquivo, o array de ponteiros para node com os caminhos para as folhas da árvore e um inteiro com o tamanho total
    de Bytes que o arquivo compactado terá. Retorna um array de unsigned char com o futuro conteúdo do arquivo comprimido.
 */
unsigned char* make_file_content(unsigned char *file_data, int file_size, node **map, int total_amount_of_bytes);

void create_final_file(unsigned char *header, unsigned char *compacted_file_content, int tree_size, int total_amount_of_bytes);


#endif //HUFFMAN_ENCODE_H
