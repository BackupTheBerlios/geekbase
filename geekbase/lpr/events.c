#include "events.h"
#include "terminal.h"

void
menu_event(MENU *work, MENUPAN *lpr, MENUPAN *edita, 
		       MENUPAN *visualizza, MENUPAN *cerca, MENUPAN *help)
{
	int key;
	int item;

	switch(key=getch())
	{
		case KEY_LEFT:
			menu_driver(work, REQ_LEFT_ITEM);
			break;
		case KEY_RIGHT:
			menu_driver(work, REQ_RIGHT_ITEM);
			break;
		case 10:
			item=item_index(current_item(work));
			switch(item)
			{
				case 0:
				       	submenu_event(work, lpr);
					break;
				case 1:
					submenu_event(work, edita);
					break;
				case 2:
					submenu_event(work, visualizza);
					break;
				case 3:
					submenu_event(work, cerca);
					break;
				case 4:
					submenu_event(work, help);
					break;	
			}
			break;
	}
}

void
submenu_event(MENU *work, MENUPAN *submenu)
{
	int key;
	int item;
	bool end=false;


	assert(work && submenu);

	menupan_show(submenu);
	lpr_refresh();

	while(!end ) {
		key=getch();
	switch(key)
	{	
		case KEY_LEFT:
			menu_driver(work, REQ_LEFT_ITEM);
			end=true;
			break;

		case KEY_RIGHT:
			menu_driver(work, REQ_RIGHT_ITEM);
			end=true;
			break;
		case KEY_UP:
			menu_driver(submenu->menu, REQ_UP_ITEM);
			break;
		case KEY_DOWN:
			menu_driver(submenu->menu, REQ_NEXT_ITEM);
			break;
		case 10:
			item=item_index(current_item(submenu->menu));
			switch(submenu->id) {
				case 0:
				        menulpr_event(item);
					break;
				case 1:
					menuedita_event(item);
					break;	
				case 2:
				       
					/*table_view();*/
					break;
				case 3:
					menucerca_event(item);
					break;
				case 4:
					menuhelp_event(item);
					break;
			}
			end=true;
			break;
	}
	lpr_refresh();
	}
	menupan_hide(submenu);
}


void
menulpr_event(int item)
{
	switch(item) {
		case 0:
			break;
		case 2:
			break;
	}
}

void
menuedita_event(int item)
{
	switch(item) {
		case 0:
			break;	
		case 1:
			break;

		case 2:
			break;
	}
}

void
menucerca_event(int item)
{
	switch(item) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
	}
}

void
menuhelp_event(int item)
{
	switch(item) {
		case 0:
			break;
		case 2:
			break;
	}
}
