#include "block.h"
#include "blocklist.h"
#include "utils.h"
#include "g_error.h"

extern unsigned g_errno;

blocklist*
blocklist_new(unsigned block_size, unsigned member_size)
{
	blocklist *temp;
	block *first;

	assert(member_size != 0);

	first = block_new(member_size, block_size);

	XMALLOC(temp, sizeof(blocklist), NULL);
   	temp->member_size = member_size;
	temp->block_size = block_size;
	temp->head = first;
	return temp;
}

int
blocklist_free(blocklist *morituro)
{
	block *b;

	assert(morituro);

	b=morituro->head;

	while(b->next!=NULL) {
		block_free(b);
		b = b->next;
	}

	free(morituro); /* die!! :) */

	return 1;
}

int
blocklist_insert_block(blocklist *bl, block *b, block *where)
{ 
	block *before;

	assert(bl && b && where);

	if(bl->head!=NULL) {

		before=bl->head;

		while(before!=where) 
			before=before->next;

		b->next=before->next;
		before->next=b;
	}
	else bl->head=b;

	bl->blocknum++;


	return 1;
}

int
blocklist_append_block(blocklist *bl, block *b)
{
	block *tmp;
	block *last;

	assert(bl && b);

	last=bl->head;
	while(tmp!=NULL) {
		last=tmp;
		tmp=tmp->next;
	}

	last->next = b;
	bl->blocknum++;

	return 1;
}

int
blocklist_pushf_block(blocklist *bl, block *b)
{
	assert(bl && b);

	b->next=bl->head;
	bl->head=b;
	bl->blocknum++;

	return 1;
}

void
blocklist_append_elem(blocklist *bl, void *data)
{
	block *tmp, *new;
	int i;

	assert(bl && bl->head);

	tmp = bl->head;
	/* go to the last block */
	while(tmp->next)
		tmp = tmp->next;

	/* the buffer is not full */
	if(tmp->buff->used < tmp->buff->size)
		buffer_add(tmp->buff, data);
	/* the buffer is full, create another block */
	else {
		new = block_new(bl->member_size, bl->block_size);
		buffer_add(new->buff, data);
		blocklist_append_block(bl, new);
	}
}

/* @todo da implementare */
void
blocklist_del_elem(blocklist *bl, unsigned index)
{
}

void*
blocklist_get_elem(blocklist *bl, unsigned index)
{
	void *buf;
	block *tmp;
	unsigned loc = 0;

	assert(bl);

	tmp = bl->head;
	while(tmp->next && loc+bl->block_size-1 < index) {
		tmp = tmp->next;
		loc += bl->block_size;
	}

	if(index < loc + bl->block_size) {
		XMALLOC(buf, bl->member_size, NULL);
		buf = buffer_get(tmp->buff, index % bl->block_size);
		return buf;
	} else
		return NULL;
}
