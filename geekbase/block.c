#include <stdlib.h>

#include "buffer.h"
#include "block.h"
#include "utils.h"
#include "errors.h"

extern unsigned geek_errno;

block *block_new(unsigned member_size, unsigned size)
{
	block *bl;

	assert(member_size != 0);

	XMALLOC(bl, sizeof(block), NULL);
	bl->buff = buffer_new(member_size, size);
	bl->next= NULL;

	return bl;
}

void block_free(block *morituro) 
{
	assert(morituro);

	buffer_free(morituro->buff);
	free(morituro); /* die!! :) */
}
