#include <stdlib.h>

#include "geekbase.h"
#include "buffer.h"

int main(/*int argc, char **argv*/)
{
	unsigned i;
	int *p;
	buffer *b = buffer_new (sizeof(int), 4);
	buffer *c = buffer_new (sizeof(int), 5);

	for (i = 0; i < 4; i++)
		buffer_add (b, (void *) &i);
	for (i = 4; i < 9; i++)
		buffer_add (c, (void *) &i);

	if(buffer_merge(b, 0, c, 0, 2) == -1) {
		printf("Sei fottuto");
		return EXIT_FAILURE;
	}

	for (i = 0; i < b->used; i++) {
		p = (int *)buffer_get(b, i);
		printf("%d ", *p);
	}
	printf("\n");

	buffer_free(b);
	buffer_free(c);

	return EXIT_SUCCESS;
}
