#include <string.h>
#include <stdlib.h>

#include "buffer.h"
#include "errors.h"
#include "utils.h"

extern unsigned geek_errno;

buffer*
buffer_new (size_t member_size, size_t size)
{
	buffer *temp;

	assert(member_size != 0);

	XMALLOC(buffer, temp, sizeof(buffer), NULL);
	temp->member_size = member_size;
	temp->used = 0;
	temp->size = size;
	if(size) {
		XMALLOC(void, temp->buf, size * member_size, NULL);
	}
	else
		temp->buf = NULL;

	return temp;
}

void buffer_free (buffer *buff)
{
	assert(buff);

	if(buff->buf)
		free(buff->buf);
	free(buff);
}

/**
 * @todo Optimize it not to always do the first XMALLOC
 **/
int
buffer_add(buffer *buff, void *data)
{
	void *tmp_buf;
	unsigned used_mem = buff->used * buff->member_size;

	assert(buff && data);
	assert(buff->used <= buff->size);

	if (buff->used == buff->size) {
		++buff->size;
	}
	XMALLOC(void, tmp_buf, buff->size * buff->member_size, -1);

	if (buff->used > 0)
		memcpy(tmp_buf, buff->buf, used_mem);
	memcpy(VOID_P (CHAR_P tmp_buf + used_mem), data, buff->member_size);
	++buff->used;

	free(buff->buf);
	buff->buf = tmp_buf;

	return 0;
}

void*
buffer_get(buffer *buff, size_t index)
{
	void *tmp_buf;

	assert(buff && buff->used <= buff->size);

	if (index >= buff->used) {
		geek_errno = ERR_ARRAY_OUT_OF_BOUNDS;
		return NULL;
	}

	XMALLOC(void, tmp_buf, buff->member_size, NULL);
	memcpy(tmp_buf, VOID_P (CHAR_P buff->buf + index * buff->member_size), buff->member_size);

	return tmp_buf;
}

int 
buffer_merge(buffer *dest, size_t destpos, buffer *src, size_t src_startpos, size_t n)
{
	void *tmp_buf;

	assert(dest && src);
	assert(dest->member_size == src->member_size);
	assert(destpos <= dest->size);
	assert(src_startpos + n <= src->used);

	/* if there's not enough memory in the destination buffer */
	if (dest->size < destpos + n) {
		/* allocate memory for the new contents */
		XMALLOC(void, tmp_buf, dest->member_size * (destpos + n), -1);
		/* if there's something to copy from the old buffer */
		if (dest->used > 0) {
			memcpy(tmp_buf, dest->buf, destpos * dest->member_size);
			free(dest->buf);
			dest->buf = tmp_buf;
			dest->size = destpos + n;
		}
	}

	memcpy(VOID_P (CHAR_P dest->buf + destpos * dest->member_size),
	       VOID_P (CHAR_P src->buf + src_startpos * dest->member_size),
	       n * dest->member_size);
	if(destpos + n > dest->used)
		dest->used = destpos + n;

	return 0;
}