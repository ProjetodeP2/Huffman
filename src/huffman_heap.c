#include "../lib/huffman_heap.h"

struct heap
{
    int size;
    void* data[MAX_HEAP_SIZE+1];
};

heap* create_heap()
{
    int i;
    heap *new_heap = (heap*)malloc(sizeof(heap));
    for (i = 0; i <= MAX_HEAP_SIZE; ++i)
    {
        new_heap->data[MAX_HEAP_SIZE] = NULL;
    }
    new_heap->size = 0;
    return new_heap;
}

int get_heap_size(heap *heap)
{
    return heap->size;
}


int get_parent_index(int index)
{
    return index >> 1;
}
int get_left_index(int index)
{
    return index << 1;
}
int get_right_index(int index)
{
    return (index << 1) + 1;
}

void enqueue_huffman_heap(heap *heap, huffman_tree *node)
{

    if(heap->size >= MAX_HEAP_SIZE)
    {
        printf("Heap overflow\n");
    }
    else
    {
        heap->data[++heap->size] = node;
        int current_index = heap->size;
        int parent_index = get_parent_index(heap->size);
        huffman_tree *current_node = (huffman_tree*)heap->data[current_index];
        huffman_tree *parent_node = (huffman_tree*)heap->data[parent_index];
        while(parent_index >= 1 && get_huffamn_node_frequency(current_node) < get_huffamn_node_frequency(parent_node))
        {
            huffman_tree_swap(current_node, parent_node);
            current_index = parent_index;
            parent_index = get_parent_index(current_index);
            current_node = (huffman_tree*)heap->data[current_index];
            parent_node = (huffman_tree*)heap->data[parent_index];
        }
    }

}
void min_heapify_huffman_heap(heap *heap, int index)
{
    int lowest;
    int left_index = get_left_index(index);
    int right_index = get_right_index(index);

    if (left_index <= heap->size && get_huffamn_node_frequency((huffman_tree*)heap->data[left_index])< get_huffamn_node_frequency((huffman_tree*)heap->data[index]))
    {
        lowest = left_index;
    }
    else
    {
        lowest = index;
    }

    if (right_index <= heap->size && get_huffamn_node_frequency((huffman_tree*)heap->data[right_index]) < get_huffamn_node_frequency((huffman_tree*)heap->data[lowest]))
    {
        lowest = right_index;
    }

    if ((huffman_tree*)heap->data[index] != (huffman_tree*)heap->data[lowest])
    {
        huffman_tree_swap((huffman_tree*)heap->data[index],(huffman_tree*)heap->data[lowest]);
        min_heapify_huffman_heap(heap, lowest);
    }
}
int is_empty(heap *heap)
{
    if (heap->size == 0 )return 1;
    return 0;
}
huffman_tree* dequeue_of_huffman_heap(heap *heap)
{
    if (is_empty(heap))
    {
        printf("Heap underflow\n");
        return NULL;
    }
    else
    {
        huffman_tree *node = (huffman_tree*)heap->data[1];

        heap->data[1] = heap->data[heap->size];

        heap->size--;

        min_heapify_huffman_heap(heap, 1);

        return node;
    }
}