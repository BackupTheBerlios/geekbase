#include <assert.h>
#include <stdlib.h>

#ifndef ERRORS_H
#define ERRORS_H

extern unsigned g_errno;

typedef enum {
	SUCCESS,
	ERR_NOMEM,
	ERR_ARRAY_OUT_OF_BOUNDS
} err_type;

void g_error(const char *msg);

#endif /* ERRORS_H */
