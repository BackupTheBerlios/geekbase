#include "events.h"

int
window_event(LPR_WINDOW *curwindow)
{
	int i=1;
	int item;
	int g_event=FOCUS_W;
	
	if(curwindow->hasfocus==false)
		return FOCUS_M;

	switch(getch())
	{
		case 9:
			g_event=FOCUS_M;
			break;
		case 27:
			g_event=shortcut(curwindow);
			break;
			
	}
	return g_event;
}

int
shortcut(LPR_WINDOW *curwindow) 
{
	int g_event=FOCUS_W;
	int i=0;
     
	switch(getch()) {
		
		case 'w':			
			curwindow->hasfocus=false;
			curwindow=curwindow->next;
			while(curwindow->hidden!=false  && i!=10) {
				curwindow=curwindow->next;	
				i++;
			}
			top_panel(curwindow->shad);
			top_panel(curwindow->body);
			curwindow->hasfocus=true;
			break;

		case 'z':
			window_hide(curwindow);
			
			while(curwindow->hidden!=false && i!=11) {
				curwindow=curwindow->next;	
				i++;
			}
			if(i==11)
				g_event=FOCUS_M;
		        else
				curwindow->hasfocus=true;
			break;
		case 'u':
			window_move(curwindow, curwindow->body->win->_begy-1, 
				    curwindow->body->win->_begx);
			break;
		case 'n':
			window_move(curwindow, curwindow->body->win->_begy+1, 
				    curwindow->body->win->_begx);
			break;
		case 'j':
			window_move(curwindow, curwindow->body->win->_begy, 
				    curwindow->body->win->_begx+1);
			break;
		case 'h':
			window_move(curwindow, curwindow->body->win->_begy, 
				    curwindow->body->win->_begx-1);
			break;	
	}
	
	return g_event;
}


void
open_window(int id, LPR_WINDOW *curwin)
{
	LPR_WINDOW *dummy;
	int i;

	assert(curwin);

	
	while(curwin->id!=id) 
		curwin=curwin->next;

	dummy=curwin;

	for(i=0;i<=10;i++) {
		dummy=dummy->next;
		dummy->hasfocus=false;
	}
	if(curwin->hidden==true)
		window_show(curwin);
	else {
		top_panel(curwin->shad);
		top_panel(curwin->body);
	}
	
	curwin->hasfocus=true;

}
