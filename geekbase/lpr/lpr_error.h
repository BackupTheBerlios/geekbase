#ifndef LPR_ERROR_H
#define LPR_ERROR_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

enum lpr_errnum {
	NO_MEM,
	TERM_SIZE,
	NO_COLOR,
	BOH
};

void lpr_error(int errnum, char *func);
char *lpr_errtype(int errnum);

#endif /* LPR_ERROR_H */ 
