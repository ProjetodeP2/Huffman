#include "../lib/linked_list.h"

node* create_list()
{
    return NULL;
}
int is_list_empty(node* head)
{
    return(head == NULL);
}

node* add_int_end(node* head, int item)
{
    int *item_of_node = (int*)malloc(sizeof(int));
    *item_of_node = item;
    if(head == NULL)
    {
        node* new_node = (node*) malloc(sizeof(node));
        new_node->item = item_of_node;
        new_node->next = head;
        return new_node;
    }
    node* aux = head;
    while(head->next != NULL)
    {
        head = head->next;
    }
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item = item_of_node;
    new_node->next = head->next;
    head->next = new_node;
    return aux;
}

node* add_unsigned_char_end(node* head, unsigned char item)
{
    unsigned char *item_of_node = (unsigned char*)malloc(sizeof(unsigned char));
    *item_of_node = item;
    if(head == NULL)
    {
        node* new_node = (node*) malloc(sizeof(node));
        new_node->item = item_of_node;
        new_node->next = head;
        return new_node;
    }

    node* aux = head;

    while(head->next != NULL) head = head->next;

    node* new_node = (node*) malloc(sizeof(node));
    new_node->item = item_of_node;
    new_node->next = head->next;
    head->next = new_node;
    return aux;
}

node* remove_last_node(node* head)
{
    node *previous = NULL;
    node *current = head;
    if(current == NULL)
    {
        return head;
    }
    while(current->next != NULL)
    {
        previous = current;
        current= current->next;
    }
    if(previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    free(current);
    return head;
}
node* copy_int_list(node *head)
{
    node *aux = head;
    node *copy = create_list();
    int *item = NULL;
    while (aux != NULL)
    {
        item = (int *)aux->item;
        copy = add_int_end(copy, *item);
        aux = aux->next;
    }
    return copy;
}
void print_int_list(node* head)
{
    node* aux = head;
    int *item = NULL;
    if (aux == NULL)printf("Lista vazia\n");
    while(aux != NULL)
    {
        item = (int *)aux->item;
        printf("%d ", *item);
        aux=aux->next;
    }
    printf("\n");
}

void print_unsigned_char_list(node *head)
{
    node* aux = head;
    unsigned char *item = NULL;
    if (aux == NULL)printf("Lista vazia\n");
    while(aux != NULL)
    {
        item = (unsigned char *)aux->item;
        printf("%c ", *item);
        aux=aux->next;
    }
    printf("\n");
}

int list_count(node* head, int size)
{
    if ( head == NULL) return size;
    list_count( head->next, ++size);
}