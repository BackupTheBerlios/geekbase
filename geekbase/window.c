#include <string.h>

#include "window.h"
#include "g_error.h"

LPR_WINDOW*
window_create(const char *title, int sizey, int sizex, int id) 
{
	LPR_WINDOW *win;


	assert(title);
	
	win=(LPR_WINDOW *)malloc(sizeof(LPR_WINDOW));
	if(!win) {
		set_error(ERR_NOMEM);
		lpr_error("window_create");
	}

	win->shad=new_panel(newwin(sizey, sizex,(LINES-sizey)/2+1, 
				   (COLS-sizex)/2+1));

	win->body=new_panel(newwin(sizey, sizex,(LINES-sizey)/2, 
				   (COLS-sizex)/2));
	win->title=strdup(title);
	win->id=id;

	box(win->body->win, 0, 0);
	box(win->shad->win, 0, 0);
	mvwprintw(win->body->win, 0, (sizex-strlen(win->title))/2,
		  win->title);
	wcolor_set(win->body->win, 1, NULL);
        wbkgd(win->body->win, COLOR_PAIR(1) | 32);
	wbkgd(win->shad->win, COLOR_PAIR(2) | 32);
	window_hide(win);
		
	return win;
}

void
window_free(LPR_WINDOW *win)
{
	assert(win);

	unpost_form(win->form);
	delwin(win->body->win);
	delwin(win->shad->win);
	del_panel(win->body);
	del_panel(win->shad);

	free_field(win->form->field[0]);
	free_field(win->form->field[1]);
	free_form(win->form);
	free(win);
}

void
window_hide(LPR_WINDOW *win)
{
	assert(win);
	
	hide_panel(win->body);
	hide_panel(win->shad);
	win->hidden=true;
	win->hasfocus=false;
}

void
window_show(LPR_WINDOW *win)
{
	assert(win);
	
	show_panel(win->shad);	
	show_panel(win->body);

	win->hidden=false;
}

void
window_move(LPR_WINDOW *win, int y, int x) 
{
	assert(win);

	if((win->body->win->_begy==1 && y==0) ||
		(win->body->win->_begx==0 && x==0))
		return;
	move_panel((win->body), y, x);
	move_panel((win->shad), y+1, x+1);

}


LPR_WINDOW*
wdbpath_create(void) 
{
	LPR_WINDOW *win;
	FIELD *field[2];
      
	
	win=window_create("Cambia path DB", 5, 30, 0);	
	field[0]=new_field(1, 26, 2, 1, 5, 0);
	field[1]=NULL;
	set_field_fore(field[0], COLOR_PAIR(1) | A_REVERSE | A_UNDERLINE);
	set_field_back(field[0], COLOR_PAIR(1)| A_UNDERLINE);
	win->form=new_form(field);
	set_form_win(win->form, win->body->win);
	set_form_sub(win->form, derwin(win->body->win, 3, 28, 1, 1));
        post_form(win->form);
	
	return win;
}

LPR_WINDOW*
winsrec_create(void)
{
	LPR_WINDOW *win;
    
	FIELD *field[5];
	int i;
		

	win=window_create("Inserisci Record", 10, 28, 1);
 
	win->field[0]=new_field(1, 9, 0, 13 ,0, 0); /* giorno */ 
	set_field_type(win->field[0], TYPE_ALPHA, 6); 
	win->field[1]=new_field(1, 2, 1, 13, 0, 0); /* da */
	set_field_type(win->field[1], TYPE_INTEGER, 1); 
	win->field[2]=new_field(1, 2, 1, 19, 0, 0); /* a */
	set_field_type(win->field[2], TYPE_INTEGER, 1); 
	win->field[3]=new_field(1, 2, 2, 13, 0, 1); /* aula */
 	set_field_type(win->field[2], TYPE_ALNUM, 1); 
	win->field[4]=new_field(1, 12, 3, 13, 0, 1); /* materia */	
 	set_field_type(win->field[2], TYPE_ALPHA, 1); 
	win->field[5]=new_field(1, 12, 4, 13, 0, 1); /* docente */
 	set_field_type(win->field[2], TYPE_ALNUM, 1); 
	win->field[6]=new_field(1, 2, 6, 12, 0, 1);
	win->field[7]=NULL;
	
	set_field_buffer(win->field[6], 0, "OK");
	field_opts_off(win->field[6], O_EDIT );
	for(i=0; i<=6; ++i) {
		set_field_fore(win->field[i], 
			       COLOR_PAIR(1) | A_UNDERLINE);
		set_field_back(win->field[i], COLOR_PAIR(1)| A_UNDERLINE);
			field_opts_off(win->field[i], O_AUTOSKIP );
	}

	win->form=new_form(win->field);

	set_form_win(win->form, win->body->win);
	set_form_sub(win->form, derwin(win->body->win, 8, 26, 1, 1));

        post_form(win->form); 

	mvwprintw(win->body->win, 1 , 1, "Giorno:");
	mvwprintw(win->body->win, 2 , 1, "Orario da:");
	mvwprintw(win->body->win, 2 , 17, "a:");
	mvwprintw(win->body->win, 3 , 1, "Aula:");
	mvwprintw(win->body->win, 4 , 1, "Materia:");
	mvwprintw(win->body->win, 5 , 1, "Docente:");
		
	return win;
}

LPR_WINDOW*
weditrec_create(void)
{
	LPR_WINDOW *win;
    
	FIELD *field[6];
	int i;
		

	win=window_create("Edita Record", 11, 28, 2);

	field[6]=new_field(1, 8, 0, 13 ,5, 0); 
	field[0]=new_field(1, 8, 1, 13 ,5, 0); 
	field[1]=new_field(1, 2, 2, 13, 5, 0);
	field[2]=new_field(1, 2, 2, 16, 5, 0);
	field[3]=new_field(1, 2, 3, 13, 5, 0);
	field[4]=new_field(1, 12, 4, 13, 5, 0);	
	field[5]=new_field(1, 12, 5, 13, 5, 0);	
	field[7]=NULL;

	for(i=0; i<=6; ++i) {
		set_field_fore(field[i], 
			       COLOR_PAIR(1) | A_REVERSE | A_UNDERLINE);
		set_field_back(field[i], COLOR_PAIR(1)| A_UNDERLINE);
	}

	win->form=new_form(field);

	set_form_win(win->form, win->body->win);
	set_form_sub(win->form, derwin(win->body->win, 9, 26, 1, 1));

        post_form(win->form); 

	mvwprintw(win->body->win, 1,  1, "Id Record:");
	mvwprintw(win->body->win, 2 , 1, "Giorno:");
	mvwprintw(win->body->win, 3 , 1, "Orario: da");
	mvwprintw(win->body->win, 3 , 4, "a:");
	mvwprintw(win->body->win, 4 , 1, "Aula:");
	mvwprintw(win->body->win, 5 , 1, "Materia:");
	mvwprintw(win->body->win, 6 , 1, "Docente:");
	mvwprintw(win->body->win, 9 , 1, "[INVIO] per modificare");
		
	return win;
}

LPR_WINDOW*
wcancrec_create(void) 
{
	LPR_WINDOW *win;
	FIELD *field[2];
      
	
	win=window_create("Elimina Record", 5, 20, 3);	
	field[0]=new_field(1, 2, 1, 11, 5, 0);
	field[1]=NULL;
	set_field_fore(field[0], COLOR_PAIR(1) | A_REVERSE | A_UNDERLINE);
	set_field_back(field[0], COLOR_PAIR(1)| A_UNDERLINE);  
	win->form=new_form(field);
	set_form_win(win->form, win->body->win);
	set_form_sub(win->form, derwin(win->body->win, 3, 18, 1, 1));
        post_form(win->form);
	mvwprintw(win->body->win, 2 , 1, "Id Record:");

	return win;
}

LPR_WINDOW*
wvisualtab_create(void) 
{
	LPR_WINDOW *win;
	int i,j=9;
	
	win=window_create("Tabella Orario", 21, 76, 4);	
	
	mvwprintw(win->body->win, 1, 1, 
		  "        L            M            M            G%s",
		  "            V");
       

	for(i=2;i<=19;i+=2) {
		
		mvwhline(win->body->win, i, 1, 0, getmaxx(win->body->win)-3);
		mvwprintw(win->body->win, i+1, 1, "%d-%d",j ,j+1);
		j++;
	}

	for(i=8;i<=73;i+=13)
		mvwvline(win->body->win, 1, i, 0, getmaxy(win->body->win)-2);
	return win;
}

LPR_WINDOW*
wcerca_create(const char *title, const char *desc, int formsize, int id) 
{
	LPR_WINDOW *win;
   	FIELD *field[2];   
      
	
	assert(desc);
	
	win=window_create(title, 16, 60, id);
    
	field[0]=new_field(1, formsize, 1, 15+strlen(desc), 5, 0);
	field[1]=NULL;
	set_field_fore(field[0], COLOR_PAIR(1) | A_REVERSE | A_UNDERLINE);
	set_field_back(field[0], COLOR_PAIR(1)| A_UNDERLINE);  
	win->form=new_form(field);
	set_form_win(win->form, win->body->win);
	set_form_sub(win->form, derwin(win->body->win, 14, 58, 1, 1));
        post_form(win->form);
	
	mvwprintw(win->body->win, 2, 1, "%s da ricercare:",desc);
       	mvwhline(win->body->win, 4, 1, 0, getmaxx(win->body->win)-2);
	mvwprintw(win->body->win, 4, 
		  (getmaxx(win->body->win)-strlen("Risultato ricerca"))/2, 
		  "Risultato ricerca");		

	return win;
}


LPR_WINDOW*
wcorario_create(void) 
{
	LPR_WINDOW *win;
	
	win=wcerca_create("Ricerca per orario", "Orario", 2, 5);
	return win;
		  
}

LPR_WINDOW*
wcaula_create(void) 
{
	LPR_WINDOW *win;
	
	win=wcerca_create("Ricerca per aula", "Aula", 2, 6);
	return win;
		  
}

LPR_WINDOW*
wcdoc_create(void) 
{
	LPR_WINDOW *win;
	
	win=wcerca_create("Ricerca per docente","Docente", 10, 7);
	return win;
		  
}

LPR_WINDOW*
wcmateria_create(void) 
{
	LPR_WINDOW *win;
	
	win=wcerca_create("Ricerca per materia", "Materia", 10, 8);
	return win;
		  
}

LPR_WINDOW*
whelp_create(void) 
{
	LPR_WINDOW *win;
   
   	
	win=window_create("Help", 20, 40, 9);
    
	mvwprintw(win->body->win, 2, 1, "M-h\t Visualizza questa finestra");
      

	return win;
}

LPR_WINDOW*
wabout_create(void) 
{
	LPR_WINDOW *win;
   
   	
	win=window_create("About", 20, 40, 10);
    
	mvwprintw(win->body->win, 2, 1, "a lain & fe[nl]x production");
      
	return win;
}

void
usrptr_window(LPR_WINDOW *win1, LPR_WINDOW *win2)
{
	assert(win1 && win2);

	win1->next=win2;
}
	      
