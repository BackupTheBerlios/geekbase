#include <stdlib.h>

#include "g_error.h"

/**
 * @brief Simplifies memory allocation
 * Controls the pointer returned by malloc.
 */
#define XMALLOC(ptr, size, retval) \
	ptr = malloc(size); \
	if (ptr == NULL) { \
		g_errno = ERR_NOMEM;	\
		return retval; \
	}

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#define VOID_P (void*)
#define CHAR_P (unsigned char*)
