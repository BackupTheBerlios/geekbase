#include <stdio.h>

#include "g_error.h"

/** Code of most recent error */
unsigned g_errno;

const char *g_errlist[] = {
	"Success",
	"You ran out of memory",
	"Wrong array index",
	"Table already axists",
	"Wrong location",
	"Could not open table",
	"Table has wrong format or is incomplete",
	"One or more arguments are not valid",
	NULL
};

void g_error(const char *msg)
{
	if(msg)
		fprintf(stderr, "%s: ", msg);

	fprintf(stderr, "%s\n", g_errlist[g_errno]);
}

void set_error(err_type err)
{
	g_errno = err;
}
