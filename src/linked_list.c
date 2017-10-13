#include "../lib/linked_list.h"


node* create_list()
{
    return NULL;
}
int is_list_empty(node* head)
{
    return(head == NULL);
}

node* add_end(node* head, int item)
{
    if(head == NULL)
    {
        node* new_node = (node*) malloc(sizeof(node));
        new_node->item = item;
        new_node->next = head;
        return new_node;
    }
    node* aux = head;
    while(head->next != NULL)
    {
        head = head->next;
    }
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
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
node* copy_list(node *head)
{
    node *aux = head;
    node *copy = create_list();
    while (aux != NULL)
    {
        copy = add_end(copy, aux->item);
        aux = aux->next;
    }
    return copy;
}
void print_list(node* head)
{
    node* aux = head;
    if (aux == NULL)printf("Lista vazia\n");
    while(aux != NULL)
    {
        printf("%d ", aux->item);
        aux=aux->next;
    }
    printf("\n");
}