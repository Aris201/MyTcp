#ifndef __NODE_LIST__
#define __NODE_LIST__

#include <stdbool.h>
#include <stdint.h>

typedef bool (*compare_func)(void* value);
typedef void (*dispose_func)(void* value);
typedef void (*callback_func)(void* value);

typedef struct _node {
	void* value;
	node_t* next;
} node_t;

node_t* create_or_add_to_node_list(node_t* list, void* value);

void foreach_node_in_node_list(node_t* list, callback_func callback_func);

void* find_from_node_list(node_t* list, compare_func compare_func);

node_t* remove_from_node_list(node_t* list, compare_func func, dispose_func dispose_func);

void close_node_list(node_t** list, dispose_func dispose_func);

#endif // !__NODE_LIST__

