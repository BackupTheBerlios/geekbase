#include "lpr_error.h"

void
lpr_error(int errnum, char *func)
{
	fprintf(stderr, "Error: %s \nIn function: %s\n\n", 
		lpr_errtype(errnum), func);
	if(!isendwin())
		endwin();
	exit(1);
}
 



char*
lpr_errtype(int errnum)
{
	char *errtype;

	switch(errnum) {
		case NO_MEM:
			errtype="Out of memory!";
			break;
		case TERM_SIZE:
			errtype="Terminal size is too little!";
			break;
		case NO_COLOR:
			errtype="Terminal does not support colors!";
			break;
		default:
			errtype="Error not recognized!";
			break;
	}
	return errtype;
}


