#include "block.h"
#include "blocklist.h"
#include "utils.h"
#include "errors.h"

extern unsigned geek_errno;

blocklist*
blocklist_new(unsigned block_size, unsigned member_size)
{
	blocklist *temp;
	block *first;

	assert(member_size != 0);

	first = block_new(block_size, 0);

	XMALLOC(temp, sizeof(blocklist), NULL);
   	temp->member_size = member_size;
	temp->block_size = block_size;
	temp->first = first;
	return temp;
}

int
blocklist_free(blocklist *morituro)
{
	block *b;

	assert(morituro);

	b=morituro->first;

	while(b->next!=NULL) {
		block_free(b);
		b = b->next;
	}

	free(morituro); /* die!! :) */

	return 1;
}

int
blocklist_insert(blocklist *bl, block *b, block *where)
{ 
	block *before;

	assert(bl && b && where);

	if(bl->first!=NULL) {

		before=bl->first;

		while(before!=where) 
			before=before->next;

		b->next=before->next;
		before->next=b;
	}
	else bl->first=b;

	bl->blocknum++;


	return 1;
}

int
blocklist_append(blocklist *bl, block *b)
{
	block *tmp;
	block *last;

	assert(bl && b);

	last=bl->first;
	while(tmp!=NULL) {
		last=tmp;
		tmp=tmp->next;
	}

	last->next=b;
	bl->blocknum++;

	return 1;
}

int
blocklist_pushf(blocklist *bl, block *b)
{
	assert(bl && b);

	b->next=bl->first;
	bl->first=b;
	bl->blocknum++;

	return 1;
}
