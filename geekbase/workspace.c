#include "workspace.h"


MENU*
menu_create(const char *choices[], const char *desc[], int nchoices)
{
 	MENU *menu;
	ITEM **items;
	int i;
   

	items=(ITEM **)calloc(5+1, sizeof(ITEM *));
	if(!items)
		lpr_error(NO_MEM, "create_menu");

	for(i=0; i<5; ++i) {
		items[i]=new_item(choices[i], desc[i]);
		if(choices[i]==SEP)
			item_opts_off(items[i], O_SELECTABLE);
	}
	items[5] = (ITEM *)NULL;
	menu=new_menu((ITEM **)items);
   
	
	return menu;
}


MENUPAN*
menu_pan_create(MENU *menu, int y, int x, int id)
{
      	MENUPAN *menupan;


	assert(menu);
	
	menupan=(MENUPAN *)malloc(sizeof(MENUPAN));
	if(!menupan) 
		lpr_error(NO_MEM, "menu_pan_create");

	menupan->id=id;
	menupan->menu=menu;
	menupan->win=new_panel(newwin(item_count(menu)+2, MSIZE, y, x));
       	menupan->sub=new_panel(derwin(menupan->win->win, 
				      item_count(menu), MSIZE-2, 1, 1));       
	wcolor_set(menupan->win->win, 1, NULL);
	set_menu_fore(menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(menu, COLOR_PAIR(1));
	set_menu_grey(menu, COLOR_PAIR(1));
	set_menu_win(menu, menupan->win->win);
	set_menu_sub(menu, menupan->sub->win);


	box(menupan->win->win, 0, 0);
	menupan_hide(menupan);

	return menupan;
}

void
menu_pan_free(MENUPAN *morituro)
{
	assert(morituro);
	
	unpost_menu(morituro->menu);
	free_menu(morituro->menu);
	delwin(morituro->win->win);
	delwin(morituro->sub->win);
	del_panel(morituro->win);
	del_panel(morituro->sub);
	
	free(morituro);
}

void
menupan_hide(MENUPAN *menupan)
{
	assert(menupan);
	
	hide_panel(menupan->win);
	hide_panel(menupan->sub);
}

void
menupan_show(MENUPAN *menupan)
{
	assert(menupan);

	show_panel(menupan->win);
	show_panel(menupan->sub);
}

MENU*
workspace_create(void) 
{
	MENU *menu;


	const char *choices[] = {
		"Lpr ",
		"Edita ",
		"Visualizza ",
		"Cerca ",
		"Help " ,
		};
      	const char *desc[] = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		};
    

	menu=menu_create(choices, desc, A_SIZE(choices));
	set_menu_format(menu, 1, A_SIZE(choices));
	set_menu_fore(menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(menu, COLOR_PAIR(1));

	post_menu(menu);
	
	return menu;

}	     


MENUPAN*
menulpr_create(void)
{
	MENU *menu;
        MENUPAN *menupan;
    
	
	const char *choices[] = {
		"Cambia path db",
		SEP,
		"Esci",
	};
	const char *desc[] = {
		"M-p",
		DSEP,
		"M-x",
	};
    

	menu=menu_create(choices, desc, A_SIZE(choices)); 
	menupan=menu_pan_create(menu, 1, 1, 0);
	post_menu(menu);

   
	return menupan;
}

MENUPAN*
menuedita_create(void)
{
	MENU *menu;
        MENUPAN *menupan;
    
	
	const char *choices[] = {
		"Inserisci Record",
		"Edita Record",
		"Elimina Record",
	};
	const char *desc[] = {
		"M-i",
		"M-e",
		"M-c  ",
	};
     

	menu=menu_create(choices, desc, A_SIZE(choices)); 
	menupan=menu_pan_create(menu, 1, ISIZE+1, 1);
	post_menu(menu);

   
	return menupan;
}


MENUPAN*
menuvisual_create(void)
{
	MENU *menu;
        MENUPAN *menupan;
    
	
	const char *choices[] = {
		"Visualizza tabella",
		NULL,
		NULL,
		
	};
	const char *desc[] = {
		"M-t",
		NULL,
		NULL,
		
	};
     

	menu=menu_create(choices, desc, 0); 
	menupan=menu_pan_create(menu, 1, 2*ISIZE+1, 2);
	post_menu(menu);

   
	return menupan;
}


MENUPAN*
menucerca_create(void)
{
	MENU *menu;
        MENUPAN *menupan;
    
	
	const char *choices[] = {
		"Cerca per Orario",
		"Cerca per Docente",
		"Cerca per Aula",
		"Cerca per Materia"
	};
	const char *desc[] = {
		"M-o ",
		"M-d ",
		"M-a ",
		NULL
	};
     

	menu=menu_create(choices, desc, A_SIZE(choices)); 
	menupan=menu_pan_create(menu, 1, 3*ISIZE+1, 3);
	post_menu(menu);

   
	return menupan;
}

MENUPAN*
menuhelp_create(void)
{
	MENU *menu;
        MENUPAN *menupan;
    
	
	const char *choices[] = {
		"Help",
		SEP,
		"About",
		NULL,
	};
	const char *desc[] = {
		"M-h",
		DSEP,
		NULL,
	};
     

	menu=menu_create(choices, desc, A_SIZE(choices)); 
	menupan=menu_pan_create(menu, 1, 4*ISIZE+1, 4);
	post_menu(menu);

   
	return menupan;
}

