#ifndef WINDOW_H
#define WINDOW_H

#include "lpr.h"
#include "workspace.h"

typedef struct lpr_window_node {
	PANEL *body;
	PANEL *shad;
	char *title;
	FORM *form;
	FIELD *field[10];
	bool hidden;
	char id;
	bool hasfocus;
	struct lpr_window_node *next;
} LPR_WINDOW;

LPR_WINDOW *window_create(const char *title, int sizey, int sizex, int id);
void window_free(LPR_WINDOW *win);
void window_hide(LPR_WINDOW *win);
void window_show(LPR_WINDOW *win);
void window_move(LPR_WINDOW *win, int y, int x);


LPR_WINDOW *wdbpath_create(void);
LPR_WINDOW *winsrec_create(void);
LPR_WINDOW *weditrec_create(void);
LPR_WINDOW *wcancrec_create(void); 
LPR_WINDOW *wvisualtab_create(void);
LPR_WINDOW *wcerca_create(const char *title, const char *desc, int formsize, int id);
LPR_WINDOW *wcorario_create(void);
LPR_WINDOW *wcaula_create(void);
LPR_WINDOW *wcdoc_create(void);
LPR_WINDOW *wcmateria_create(void);
LPR_WINDOW *whelp_create(void);
LPR_WINDOW *wabout_create(void);

void usrptr_window(LPR_WINDOW *win1, LPR_WINDOW *win2);

#endif /* WINDOW_H */
