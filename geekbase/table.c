#include "table.h"

int
table_create (char *name, table *tab)
{
	if ( !name )
		return 1;

	if ( !tab ) {
		XMALLOC(tab, sizeof(table), 1);
	}

	tab->name = malloc(strlen(name));
	strcpy(tab->name, name);
	tab->parent = NULL;

	return 0;
}

