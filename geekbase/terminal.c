#include "terminal.h"
#include "workspace.h"

void
lpr_refresh(void) 
{
	termcontrol();
	mvchgat(0, ISIZE*5-1, COLS-(ISIZE*5-1), A_NORMAL, 1, NULL);
	update_panels();
	doupdate();
}

void
termcontrol(void)
{
	if(LINES<24 || COLS<80) 
		lpr_error(TERM_SIZE, "lpr_refresh");	
}

