#include "lpr.h"
#include "workspace.h"
#include "terminal.h"


void lpr_refresh(void);

int main()
{
	MENU *workspace;
	MENUPAN *menulpr;
	MENUPAN *menuedita;
	MENUPAN *menuvisual;
	MENUPAN *menucerca;
	MENUPAN *menuhelp;

	initscr();
	if(has_colors()) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_BLACK, COLOR_BLUE);
	}
//	else msgbox("Warning: terminal does not support colors!");
	keypad(stdscr, TRUE);

	termcontrol();
	curs_set(0);
	cbreak();
	noecho();
     

	workspace=workspace_create();

	menulpr=menulpr_create();
	menuedita=menuedita_create();
	menuvisual=menuvisual_create();
	menucerca=menucerca_create();
	menuhelp=menuhelp_create();

	lpr_refresh();
      		
 	while(1)
	{
		menu_event(workspace, menulpr, menuedita, 
			   menuvisual, menucerca, menuhelp);
		lpr_refresh();				
	}	

	endwin();
}

