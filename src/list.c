#include "../lib/list.h"

typedef struct node
{
	void *item;
	struct node *next;
}node;

node* create_empty_list()
{
	return NULL;
}

node* add_tail(node* head, void* item)
{
	node* new_node = malloc(sizeof(node));
	new_node->item = item;
	
	if (head == NULL)
	{
		new_node->next = head;
		return new_node;
	}

	else
	{
		node* aux = head;

		while(head->next != NULL) 
		{
			head = head->next;
		}

		new_node->next = head->next;
		head->next = new_node;
		return aux;
	}
}

node* remove_last(node *head, node *previous, node *current)
{
	char removed = '-1';
	
	if(current == NULL)
	{
		printf("%c\n", removed);
		return NULL;	
	}

	else if (current->next == NULL)
	{
		removed = *((unsigned char*)current->item);	
		free(current);
		printf("%c\n", removed);
		return NULL;
	} 

	while(current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	removed = *((unsigned char*)current->item);
	previous->next = NULL;
	free(current);
	printf("%c\n", removed);

	return head;
}

node* copy_list(node* list1, node* list2)
{
	node *aux1 = list1;
	while(aux1 != NULL) 
	{
		list2 = add_tail(list2, aux1->item);	
		aux1 = aux1->next;
	}
	
	return list2;
}

void print(node* head)			
{
	if(head == NULL) 
	{
		printf("\n");
		return;	
	}
	printf("%c ", *((unsigned char*)head->item));
	print(head->next);
}
