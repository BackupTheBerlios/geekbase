#ifndef EVENTS_H
#define EVENTS_H

#include "lpr.h"
#include "workspace.h"
#include "window.h"

enum G_EVENT {
	FOCUS_M,
	FOCUS_W,
	LPR_EXIT,
};

int menu_event(MENU *work , MENUPAN *lpr, MENUPAN *edita, 
		MENUPAN *visualizza, MENUPAN *cerca, 
		MENUPAN *help, LPR_WINDOW *curwin);
int submenu_event(MENU *work, MENUPAN *submenu, LPR_WINDOW *curwin);

int menulpr_event(int item, LPR_WINDOW *curwin);
int menuedita_event(int item, LPR_WINDOW *curwin);
int  menucerca_event(int item, LPR_WINDOW *curwin);
void menuhelp_event(int item);

int window_event(LPR_WINDOW *curwindow);
int shortcut(LPR_WINDOW *curwindow);
void open_window(int id, LPR_WINDOW *curwin);


#endif /* EVENTS_H */
