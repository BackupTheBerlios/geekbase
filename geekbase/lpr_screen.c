#include "lpr_screen.h"


LPR_WINDOW*
lpr_init_windows(void)
{
	LPR_WINDOW *first;
	LPR_WINDOW *win1;
	LPR_WINDOW *win2;
	
	first=wdbpath_create();
	win1=winsrec_create();
	win2=weditrec_create();
       
      
	usrptr_window(first, win1);
	usrptr_window(win1, win2);
	
	win1=win2;
	win2=wcancrec_create();
      	usrptr_window(win1, win2);
	
	win1=win2;
	win2=wvisualtab_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=wcorario_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=wcdoc_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=wcaula_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=wcmateria_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=whelp_create();
	usrptr_window(win1, win2);

	win1=win2;
	win2=wabout_create();
	usrptr_window(win1, win2);
      
    
	usrptr_window(win2, first);

	return first;
}



