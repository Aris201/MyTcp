#include <stdlib.h>
#include <assert.h>

#include "node_list.h"


node_t* create_or_add_to_node_list(node_t* list, void* value)
{
	node_t* current_node = list;
	node_t* added_node = NULL;

	added_node = (node_t*)malloc(sizeof(node_t));
	added_node->value = value;
	added_node->next = NULL;

	if (NULL == list)
	{
		return added_node;
	}

	while (NULL != current_node->next)
	{
		current_node = current_node->next;
	}

	current_node->next = added_node;
	return list;
}

void foreach_node_in_node_list(node_t* list, callback_func callback_func)
{
	while (NULL != list)
	{
		callback_func(list->value);
		list = list->next;
	}
}

void* find_from_node_list(node_t* list, compare_func compare_func)
{
	while (NULL != list)
	{
		if (true == compare_func(list->value))
			return list->value;

		list = list->next;
	}

	return NULL;
}

node_t* remove_from_node_list(node_t* list, compare_func func, dispose_func dispose_func)
{
	node_t* prev = NULL;
	node_t* current = list;

	if (NULL == list)
	{
		return NULL;
	}

	if (true == func(list->value))
	{
		list = list->next;
		goto l_cleanup;
	}

	
	while (NULL != current)
	{
		if (true == func(current->value))
		{
			prev->next = current->next;
			goto l_cleanup;
		}

		prev = current;
		current = current->next;
	}

l_cleanup:
	dispose_func(&current->value);
	(void)free(current);
	return list;
}

void close_node_list(node_t** list, dispose_func dispose_func)
{
	node_t* next = NULL;
	node_t* current = NULL;

	if (list != NULL)
	{
		current = *list;
		
		while (NULL != current)
		{
			next = current->next;
			dispose_func(&current->value);
			(void)free(current);
			current = next;
		}

		*list = NULL;
	}
}