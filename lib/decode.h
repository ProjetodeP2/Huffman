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

*/
huffman_tree* get_huffman_tree(huffman_tree* tree, unsigned char* pre_order, int tree_size, int* counter);


#endif //HUFFMAN_DECODE_H
