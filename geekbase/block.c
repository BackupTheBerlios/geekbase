#include <stdlib.h>

#include "buffer.h"
#include "block.h"
#include "utils.h"
#include "errors.h"

extern unsigned geek_errno;

block *block_new(size_t member_size, size_t size)
{
	block *bl;

	assert(member_size!= 0);

	XMALLOC(block, bl, sizeof(block),NULL);
	bl->buff = buffer_new(member_size, size);
	bl->next= NULL;

	return bl;
}

void block_free(block *morituro) 
{
	buffer_free(morituro->buff);
	free(morituro); /* die!! :) */
}
