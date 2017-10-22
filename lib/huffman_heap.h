#ifndef HUFFMAN_HUFFMAN_HEAP_H
#define HUFFMAN_HUFFMAN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_tree.h"
#define MAX_HEAP_SIZE 256
/*
	Define o tipo abstrato 'heap', cujo a struct contém
	o tamanho atual da heap, e um array de poteiros para void com seu tamanho máximo.
*/
typedef struct heap
{
    int size;
    void* data[MAX_HEAP_SIZE+1];
}heap;

/*
	Retorna uma heap com o tamanho atual zero e cada elemento do array de ponteiros, data, apontando para NULL.
*/
heap* create_heap();

/*
	Retorna o indice para o pai do elemeto de indice 'i' da heap.
*/
int get_parent_index(heap *heap, int index);

/*
	Retorna o indice para o elemento à esquerda do elemeto de indice 'i' da heap.
*/
int get_left_index(heap *heap, int index);

/*
	Retorna o indice para o elemento à direita do elemeto de indice 'i' da heap.
*/
int get_right_index(heap *heap, int index);

/*
	Retorna o elemento, no índice 'i', de uma heap que contém itens do tipo unsigned char.
*/
unsigned char unsigned_char_item_of_huffman_heap(heap *heap, int index);

/*
	Adiciona um elemento do tipo huffman_tree à nossa heap  respeitando as características de uma min-heap.
*/
void enqueue_huffman_heap(heap *heap, huffman_tree *node);

/*
	Serve para manter as características de uma min_heap, no qual todos os nós devem ser maiores ou iguais aos seus pais (exceto a raíz).
	Recebe o indice 'i' e o compara com os valores do elemento em 'i' com os de sua direita e esquerda para verificar qual o menor, depois, troca seus valores, até o valor
	do índice ficar na posição correta da heap.
*/
void min_heapify_huffman_heap(heap *heap, int i);

/*
	Retorna 1 se a heap estiver vazia e 0 se não estiver.
*/
int is_empty(heap *heap);

/*
	Retorna o primeiro elemento(no caso de menor frequência) de uma min_heap que armazena elementos do tipo huffman_tree.
*/
huffman_tree* dequeue_of_huffman_heap(heap *heap);

/*
	Imprime a heap que armanazena elementos com items do tipo unsigned char.
*/
void print_unsigned_char_huffman_heap(heap *heap);


#endif //HUFFMAN_HUFFMAN_HEAP_H
