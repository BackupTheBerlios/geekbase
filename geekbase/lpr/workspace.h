#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "lpr.h"


#define SEP "------------------"
#define DSEP "---"
#define MSIZE 25
#define ISIZE 13

typedef struct {
	PANEL *win;
	PANEL *sub;
	MENU *menu;
	int id;
} MENUPAN;


MENU *menu_create(const char *choices[], const char *desc[], int nchoices);

MENUPAN *menu_pan_create(MENU *menu, int y, int x, int id);
void menupan_hide(MENUPAN *menupan);
void menupan_show(MENUPAN *menupan);

MENU *workspace_create(void);

MENUPAN *menulpr_create(void);
MENUPAN *menuedita_create(void);
MENUPAN *menuvisual_create(void);
MENUPAN *menucerca_create(void);
MENUPAN *menuhelp_create(void);

#endif /* WORKSPACE_H */
