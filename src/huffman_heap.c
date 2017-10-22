#include "../lib/huffman_heap.h"

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

int get_parent_index(heap *heap, int index)
{
    return index >> 1;
}
int get_left_index(heap *heap, int index)
{
    return index << 1;
}
int get_right_index(heap *heap, int index)
{
    return (index << 1) + 1;
}
unsigned char unsigned_char_item_of_huffman_heap(heap *heap, int index)
{
    huffman_tree *aux = (huffman_tree*)heap->data[index];
    return *((unsigned char*)((aux->item)));
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
        int parent_index = get_parent_index(heap, heap->size);
        huffman_tree *current_node = (huffman_tree*)heap->data[current_index];
        huffman_tree *parent_node = (huffman_tree*)heap->data[parent_index];
        while(parent_index >= 1 && current_node->frequency < parent_node->frequency)
        {
            huffman_tree_swap(current_node, parent_node);
            current_index = parent_index;
            parent_index = get_parent_index(heap, current_index);
            current_node = (huffman_tree*)heap->data[current_index];
            parent_node = (huffman_tree*)heap->data[parent_index];
        }

    }

}
void min_heapify_huffman_heap(heap *heap, int i)
{
    int lowest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if (left_index <= heap->size && ((huffman_tree*)heap->data[left_index])->frequency < ((huffman_tree*)heap->data[i])->frequency)
    {
        lowest = left_index;
    }
    else
    {
        lowest = i;
    }

    if (right_index <= heap->size && ((huffman_tree*)heap->data[right_index])->frequency < ((huffman_tree*)heap->data[lowest])->frequency)
    {
        lowest = right_index;
    }

    if ((huffman_tree*)heap->data[i] != (huffman_tree*)heap->data[lowest])
    {
        huffman_tree_swap((huffman_tree*)heap->data[i],(huffman_tree*)heap->data[lowest]);
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
void print_unsigned_char_huffman_heap(heap *heap)
{
    if (is_empty(heap))
    {
        printf("Empty heap\n");
        return;
    }
    int i;
    huffman_tree *current_node = NULL;
    for (i = 1; i <= heap->size; ++i)
    {
        current_node = (huffman_tree*)heap->data[i];
        printf("%c ", *((unsigned char*)current_node->item));
    }
    printf("\n");
}
