#include <assert.h>
#include <stdlib.h>

#ifndef G_ERROR_H
#define G_ERROR_H

extern unsigned g_errno;

typedef enum {
	SUCCESS,
	ERR_NOMEM,
	ERR_ARRAY_OUT_OF_BOUNDS,
	ERR_TABLE_EXISTS,
	ERR_WRONG_LOCATION
} err_type;

void g_error(const char *msg);

#endif /* G_ERROR_H */
