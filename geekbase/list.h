#ifndef LIST_H
#define LIST_H

#include "g_error.h"

typedef struct elem {
	int loc;
	void *buf;
	struct elem *next;
} elem;

typedef struct {
	unsigned elem_size;
	elem *head;
} list;

list *list_new(unsigned elem_size);
list *list_free(list *l);
list *list_ins_node(list *l, int loc, void *node);
list *list_del_node(list *l, int loc);
void *list_search(list *l, int loc);

#endif /* LIST_H */
