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
	elem *tmp, *dead;

	assert(l);

	tmp = l->head;
	while(tmp != NULL) {
		dead = tmp;
		free(dead->buf);
		free(dead);
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
		while(tmp->next != NULL && tmp->next->loc < loc)
			tmp = tmp->next;

		XMALLOC(new, sizeof(elem), NULL);
		new->loc = loc;
		XMALLOC(new->buf, l->elem_size, NULL);
		memcpy(new->buf, node, l->elem_size);
		new->next = tmp->next;
		tmp->next = new;

		if(new->next != NULL && new->loc == new->next->loc) {
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
list_append(list *l, int loc, void *node)
{
	elem *last, *new;

	assert(l);

	if(l->head == NULL) {
		XMALLOC(new, sizeof(elem), NULL);
		new->loc = loc;
		XMALLOC(new->buf, l->elem_size, NULL);
		memcpy(new->buf, node, l->elem_size);
		new->next = NULL;
		l->head = new;
	} else {
		last = l->head;
		while(last->next != NULL)
			last = last->next;
		XMALLOC(new, sizeof(elem), NULL);
		new->loc = loc > last->loc ? loc : last->loc + 1;
		XMALLOC(new->buf, l->elem_size, NULL);
		memcpy(new->buf, node, l->elem_size);
		new->next = NULL;
		last->next = new;
	}

	return l;
}

list*
list_del_node(list *l, int loc)
{
	elem *cur, *prev;

	assert(l);

	if(l->head == NULL)
		return l;
	else {
		prev = l->head;
		if(prev->loc == loc) {
			l->head = prev->next;
			free(prev);
			return l;
		}
		cur = prev->next;
		while(cur != NULL && cur->loc != loc) {
			prev = cur;
			cur = cur->next;
		}
		if(cur) {
			prev->next = cur->next;
			free(cur);
		}
	}

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

int
list_count_nodes(list *l)
{
	elem *tmp;
	int count=0;

	assert(l);

	tmp = l->head;
	while(tmp) {
		++count;
		tmp = tmp->next;
	}

	return count;
}
