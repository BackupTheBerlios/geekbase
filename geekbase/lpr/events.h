#ifndef EVENTS_H
#define EVENTS_H

#include "lpr.h"
#include "workspace.h"

void menu_event(MENU *work , MENUPAN *lpr, MENUPAN *edita, 
		MENUPAN *visualizza, MENUPAN *cerca, 
		MENUPAN *help);
void submenu_event(MENU *work, MENUPAN *submenu);

void menulpr_event(int item);
void menuedita_event(int item);
void menucerca_event(int item);
void menuhelp_event(int item);
#endif /* EVENTS_H */
