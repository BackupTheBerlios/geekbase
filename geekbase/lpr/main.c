#include "lpr.h"
#include "workspace.h"
#include "terminal.h"
#include "events.h"
#include "window.h"

void lpr_refresh(void);


int main()
{
	MENU *workspace;
	MENUPAN *menulpr;
	MENUPAN *menuedita;
	MENUPAN *menuvisual;
	MENUPAN *menucerca;
	MENUPAN *menuhelp;
	LPR_WINDOW *curwin;
	int g_event=FOCUS_M;	
	int i=0;


	initscr();

	if(has_colors()) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_BLACK, COLOR_BLACK);
		init_pair(3, COLOR_BLACK, COLOR_WHITE);
		wbkgd(stdscr, COLOR_PAIR(3) | 32);
	}

	keypad(stdscr, TRUE);
	raw();
	nodelay(stdscr, TRUE);
	timeout(50);
	termcontrol();
/*	curs_set(0);*/
	cbreak();
	noecho();
     
	curwin=lpr_init_windows();
	
	workspace=workspace_create();
	menulpr=menulpr_create();
	menuedita=menuedita_create();
	menuvisual=menuvisual_create();
	menucerca=menucerca_create();
	menuhelp=menuhelp_create();
	
	while(g_event!=LPR_EXIT)
	{
		lpr_refresh();	
		
		if(g_event==FOCUS_M) 
			g_event=menu_event(workspace, menulpr, menuedita, 
					   menuvisual, menucerca, menuhelp,
					   curwin);
	       	if(g_event==FOCUS_W) {
			while(curwin->hasfocus==false && i!=11) {
					curwin=curwin->next;	
					i++;
			}
			i=0;
			g_event=window_event(curwin);
		      
		}
			      
	}
	

    

	endwin();
}

