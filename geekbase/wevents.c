#include "events.h"
#include <string.h>
#include <ctype.h>
#include "table.h"
#include "workspace.h"

int hour(int start, int end, table *tab, record *rec);
int day(char *buf);

int wevent(LPR_WINDOW *curwin, int key, table *tab);
int insrec_wevent(LPR_WINDOW *curwin, int key, table *tab);
int editrec_wevent(LPR_WINDOW *curwin, int key, table *tab);

int
window_event(LPR_WINDOW *curwindow,table *tab)
{
	int i = 1;
	int item;
	int g_event = FOCUS_W;
	int key;

	if (curwindow->hasfocus == false)
		return FOCUS_M;

	switch (key=getch())
	{
		case 9:
			g_event = FOCUS_M;
			break;
		case 27:
			g_event = shortcut (curwindow);
			break;
		default:
			g_event = wevent (curwindow, key, tab); 
			break;
	}
	return g_event;
}

int
shortcut (LPR_WINDOW * curwindow)
{
	int g_event = FOCUS_W;
	int i = 0;

	switch (getch ())
	{

		case 'w':
			curwindow->hasfocus = false;
			curwindow = curwindow->next;
			while (curwindow->hidden != false && i != 10)
			{
				curwindow = curwindow->next;
				i++;
			}
			top_panel (curwindow->shad);
			top_panel (curwindow->body);
			curwindow->hasfocus = true;
			break;

		case 'z':
			window_hide (curwindow);

			while (curwindow->hidden != false && i != 11)
			{
				curwindow = curwindow->next;
				i++;
			}
			if (i == 11)
				g_event = FOCUS_M;
			else
				curwindow->hasfocus = true;
			break;
		case 'u':
			window_move(curwindow, curwindow->body->win->_begy - 1,
			            curwindow->body->win->_begx);
			break;
		case 'n':
			window_move(curwindow, curwindow->body->win->_begy + 1,
				    curwindow->body->win->_begx);
			break;
		case 'j':
			window_move(curwindow, curwindow->body->win->_begy,
				    curwindow->body->win->_begx + 1);
			break;
		case 'h':
			window_move(curwindow, curwindow->body->win->_begy,
				    curwindow->body->win->_begx - 1);
			break;	
	}

	return g_event;
}


void
open_window (int id, LPR_WINDOW *curwin)
{
	LPR_WINDOW *dummy;
	int i;

	assert (curwin);


	while (curwin->id != id)
		curwin = curwin->next;

	dummy = curwin;

	for (i = 0; i <= 10; i++)
	{
		dummy = dummy->next;
		dummy->hasfocus = false;
	}
	if (curwin->hidden == true)
		window_show (curwin);
	else
	{
		top_panel (curwin->shad);
		top_panel (curwin->body);
	}

	curwin->hasfocus = true;

}

int
wevent(LPR_WINDOW *curwin, int key, table *tab)
{
	int g_event=FOCUS_W;

	switch(curwin->id) {
		case 1:
			g_event = insrec_wevent(curwin, key, tab);
	}
		
	return g_event;
	
}

int
insrec_wevent(LPR_WINDOW *curwin, int key, table *tab)
{
	int g_event=FOCUS_W;
	record *rec=NULL;
	int i=-1, dummy;
	
	switch(key) {
	case KEY_UP:		
		if(curwin->form->current == curwin->field[1])
			form_driver(curwin->form, REQ_LEFT_FIELD);
		else form_driver(curwin->form, REQ_UP_FIELD);
		break;
	case KEY_DOWN:
		if(curwin->form->current == curwin->field[1]){
			form_driver(curwin->form, REQ_RIGHT_FIELD);
		}
		else {
			form_driver(curwin->form, REQ_DOWN_FIELD);
		}
		      
		break;
	case KEY_LEFT:
		form_driver(curwin->form, REQ_LEFT_CHAR);
		break;
	case KEY_RIGHT:
		form_driver(curwin->form, REQ_RIGHT_CHAR);
		break;
	      
	case KEY_DC:
		form_driver(curwin->form, REQ_DEL_CHAR);
		break;	
	case KEY_BACKSPACE:
		form_driver(curwin->form, REQ_LEFT_CHAR);
		form_driver(curwin->form, REQ_DEL_CHAR);
		break;
	case 10:
		if(curwin->form->current != curwin->field[6])
			break;
		
		set_current_field(curwin->form, curwin->field[6]);
			
		/* ID */
		if (table_exists("orario")) {
			rec = blocklist_get_elem(tab->records, i);
			while(rec)
				rec = blocklist_get_elem(tab->records, i++);
		} else i=0;

		rec = malloc(sizeof(record));
		rec->parent = tab;
		rec->values = malloc(7 * sizeof(cell));

		rec->values[0].type = TYPE_INT;
		rec->values[0].val.v_int = i;
	     

		/* Giorno */

		rec->values[1].type = TYPE_INT;
		dummy = day(field_buffer(curwin->field[0], 0));
				



		if(dummy != -1)
			rec->values[1].val.v_int= dummy;
			
		else {
			beep();
			flash();
			break;
		}
    
	    
			
		/* Da a */
	       

		dummy = hour(atoi(field_buffer(curwin->field[1],
					       0)),
			     atoi(field_buffer(curwin->field[2],
					       0)),tab, rec);
		if(dummy == 0) {
			rec->values[2].type = TYPE_INT;
			rec->values[2].val.v_int = 
	 			atoi(field_buffer(curwin->field[1],0)); 
			
			rec->values[3].type = TYPE_INT;
			rec->values[3].val.v_int = 
		 		atoi(field_buffer(curwin->field[2],0)); 

		} else {

			beep();
			flash();
			break;
		}
	   
		
		/* Aula */	       
		rec->values[4].type = TYPE_STRING;
		rec->values[4].val.v_string = 
	 		strndup(field_buffer(curwin->field[3], 0), 2); 
		/* Materia */ 
		rec->values[5].type = TYPE_STRING;
		rec->values[5].val.v_string = 
			strndup(field_buffer(curwin->field[4], 0), 12); 
		/* Docente */
		rec->values[6].type = TYPE_STRING;
		rec->values[6].val.v_string = 
 			strndup(field_buffer(curwin->field[5], 0), 12); 
		
		
		if(rec->values[1].val.v_int ||
		   rec->values[2].val.v_int)
			
			
			
		
		blocklist_append_elem(tab->records, (void*)rec);
	       
			
		table_save(tab);
		window_hide(curwin);
		break;
	default:
		form_driver(curwin->form, key);
		break;

	}
		
	return g_event;
}

int 
day(char *buf)
{
	int i=0, day_n=-1;
	char *day;
	const char *names[] = {
		"lunedi   ",
		"martedi  ",
		"mercoledi",
		"giovedi  ",
		"venerdi  "
	};

	day=strndup(buf, 10);
     
	
	while(day_n != 0 && i<5)
		day_n=strcasecmp(day, names[i++]);
	if(day_n != 0)
		return -1;
	return i-1;
	      
}

int
hour(int start, int end, table *tab, record *rec)
{
	int i=0, s ,e;
	record *dummy;


	if(start < 9 || end > 18) 
		return 1;

	if(start > end || start == end) 
		return 1;

	if(table_exists("orario")) {
		dummy = blocklist_get_elem(tab->records, i);
		while(dummy && rec->values[0].val.v_int != 
		      dummy->values[0].val.v_int) {
			/* same day */
			if(dummy->values[1].val.v_int == 
			   dummy->values[1].val.v_int) {
				s = dummy->values[2].val.v_int;
				e = dummy->values[3].val.v_int;
			
				if(start ==  s || end == e)
					return 1;
				if(start <  s && end > e)
					return 1;
				if(start > s && end < e)
					return 1;
				if(start >s  && end > e && start < e)
					return 1;
				if(start <  s && end < e && end > s )
					return 1;
			}
			dummy = blocklist_get_elem(tab->records, i++);
		}	
	}

	return 0;
}


int
editrec_wevent(LPR_WINDOW *curwin, int key, table *tab)
{
	int g_event=FOCUS_W;
	record *rec=NULL;
	int i=-1, dummy;
	
	switch(key) {
	case KEY_UP:		
		if(curwin->form->current == curwin->field[2])
			form_driver(curwin->form, REQ_LEFT_FIELD);
		else form_driver(curwin->form, REQ_UP_FIELD);
		break;
	case KEY_DOWN:
		if(curwin->form->current == curwin->field[2]){
			form_driver(curwin->form, REQ_RIGHT_FIELD);
		}
		else {
			form_driver(curwin->form, REQ_DOWN_FIELD);
		}
		      
		break;
	case KEY_LEFT:
		form_driver(curwin->form, REQ_LEFT_CHAR);
		break;
	case KEY_RIGHT:
		form_driver(curwin->form, REQ_RIGHT_CHAR);
		break;	      
	case KEY_DC:
		form_driver(curwin->form, REQ_DEL_CHAR);
		break;	
	case KEY_BACKSPACE:
		form_driver(curwin->form, REQ_LEFT_CHAR);
		form_driver(curwin->form, REQ_DEL_CHAR);
		break;
	case 10:
		if(curwin->form->current != curwin->field[7])
			break;
	}
	
	return g_event;
}

