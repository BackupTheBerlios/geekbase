#include <stdio.h>

#include "g_error.h"

/** Code of most recent error */
unsigned g_errno;

const char *g_errlist[] = {
	"Success",
	"You ran out of memory",
	"Wrong array index",
	NULL
};

void g_error(const char *msg)
{
	if(msg)
		printf("%s: ", msg);

	printf("%s\n", g_errlist[g_errno]);
}
