#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "utils.h"

list*
list_new(unsigned elem_size)
{
	list *l;

	assert(elem_size > 0);

	XMALLOC(l, sizeof(list), NULL);
	l->elem_size = elem_size;
	l->head = NULL;

	return l;
}

list*
list_free(list *l)
{
	elem *tmp;

	assert(l);

	tmp = l->head;
	while(tmp != NULL) {
		free(tmp->buf);
		free(tmp);
		tmp = tmp->next;
	}

	free(l);

	return NULL;
}

list*
list_ins_node(list *l, int loc, void *node)
{
	elem *tmp, *new;

	assert(l);

	if(l->head == NULL) {
		XMALLOC(new, sizeof(elem), NULL);
		new->loc = loc;
		XMALLOC(new->buf, l->elem_size, NULL);
		memcpy(new->buf, node, l->elem_size);
		new->next = NULL;
		l->head = new;
	} else {
		tmp = l->head;
		while(tmp->next->loc < loc)
			tmp = tmp->next;

		XMALLOC(new, sizeof(elem), NULL);
		new->loc = loc;
		XMALLOC(new->buf, l->elem_size, NULL);
		memcpy(new->buf, node, l->elem_size);
		new->next = tmp->next;
		tmp->next = new;

		if(new->loc == new->next->loc) {
			tmp = new->next;
			while(tmp->next != NULL) {
				tmp->loc++;
				tmp= tmp->next;
			}
		}
	}

	return l;
}

list*
list_del_node(list *l, int loc)
{
	assert(l);

	return l;
}

void*
list_search(list *l, int loc)
{
	elem *tmp;

	assert(l);

	tmp = l->head;
	while(tmp != NULL) {
		if(tmp->loc == loc)
			return tmp->buf;
		tmp = tmp->next;
	}

	return NULL;
}
