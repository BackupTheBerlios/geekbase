#include "events.h"
#include "terminal.h"

int
menu_event (MENU * work, MENUPAN * lpr, MENUPAN * edita,
	    MENUPAN * visualizza, MENUPAN * cerca, MENUPAN * help,
	    LPR_WINDOW * curwin)
{

	int item;
	int g_event = FOCUS_M;


	switch (getch ())
	{
	case KEY_LEFT:
		menu_driver (work, REQ_LEFT_ITEM);
		break;
	case KEY_RIGHT:
		menu_driver (work, REQ_RIGHT_ITEM);
		break;
	case 10:
		item = item_index (current_item (work));
		switch (item) {
		case 0:
			g_event = submenu_event (work, lpr, curwin);
			break;
		case 1:
			g_event = submenu_event (work, edita, curwin);
			break;
		case 2:
			g_event =
				submenu_event (work, visualizza, curwin);
			break;
		case 3:
			g_event = submenu_event (work, cerca, curwin);
			break;
		case 4:
			g_event = submenu_event (work, help, curwin);
			break;
		}
		break;
	case 9:
		g_event = FOCUS_W;
		break;

	}
	return g_event;
}

int
submenu_event (MENU * work, MENUPAN * submenu, LPR_WINDOW * curwin)
{
	int key;
	int item;
	bool end = false;
	int g_event = FOCUS_M;


	assert (work && submenu);

	menupan_show (submenu);
	lpr_refresh ();

	while (!end)
	{
		key = getch ();
		switch (key)
		{
		case KEY_LEFT:
			menu_driver (work, REQ_LEFT_ITEM);
			end = true;
			break;

		case KEY_RIGHT:
			menu_driver (work, REQ_RIGHT_ITEM);
			end = true;
			break;
		case KEY_UP:
			menu_driver (submenu->menu, REQ_UP_ITEM);
			break;
		case KEY_DOWN:
			menu_driver (submenu->menu, REQ_NEXT_ITEM);
			break;
		case 9:
			g_event = FOCUS_W;
			end = true;
			break;
		case 10:
			item = item_index (current_item (submenu->menu));
			switch (submenu->id)
			{
			case 0:
				g_event = menulpr_event (item, curwin);
				break;
			case 1:
				menuedita_event (item, curwin);
				g_event = FOCUS_W;
				break;
			case 2:

				open_window (4, curwin);
				g_event = FOCUS_W;
				break;
			case 3:
				menucerca_event (item, curwin);
				g_event = FOCUS_W;
				break;
			case 4:
				menuhelp_event (item, curwin);
				g_event = FOCUS_W;
				break;
			}
			end = true;
			break;
		}
		lpr_refresh ();
	}
	menupan_hide (submenu);
	return g_event;
}


int
menulpr_event (int item, LPR_WINDOW * curwin)
{
	int g_event = FOCUS_M;

	switch (item)
	{
	case 0:
		open_window (0, curwin);
		g_event = FOCUS_W;
		break;
	case 2:
		g_event = LPR_EXIT;
		break;
	}
	return g_event;
}

int
menuedita_event (int item, LPR_WINDOW * curwin)
{
	int g_event = FOCUS_M;
	switch (item)
	{
	case 0:
		open_window (1, curwin);
		g_event = FOCUS_W;
		break;
	case 1:
		open_window (2, curwin);
		g_event = FOCUS_W;
		break;

	case 2:
		open_window (3, curwin);
		g_event = FOCUS_W;
		break;
	}

	return g_event;
}

int
menucerca_event (int item, LPR_WINDOW * curwin)
{
	int g_event = FOCUS_M;

	switch (item)
	{
	case 0:
		open_window (5, curwin);
		g_event = FOCUS_W;
		break;
	case 1:
		open_window (6, curwin);
		g_event = FOCUS_W;
		break;
	case 2:
		open_window (7, curwin);
		g_event = FOCUS_W;
		break;
	case 3:
		open_window (8, curwin);
		g_event = FOCUS_W;
		break;

	}
	return g_event;
}

int
menuhelp_event (int item, LPR_WINDOW * curwin)
{
	int g_event = FOCUS_M;

	switch (item)
	{
	case 0:
		open_window (9, curwin);
		break;
	case 2:
		open_window (10, curwin);
		break;
	}
	return g_event;
}
