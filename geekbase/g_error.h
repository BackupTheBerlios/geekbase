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
	ERR_WRONG_LOCATION,
	ERR_OPEN_TABLE,
	ERR_INVALID_TABLE,
	ERR_INVALID_ARG,
	ERR_TERM_SIZE
} err_type;

void g_error(const char *msg);
void set_error(err_type err);
void lpr_error(const char *msg);

#endif /* G_ERROR_H */
