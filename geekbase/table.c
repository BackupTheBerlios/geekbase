#include "table.h"

int table_create (char *name, struct table *tab)
{
	if ( !name )
		return 1;

	if ( !tab )
		tab = malloc (sizeof(struct table));

	tab->name = malloc(strlen(name));
	strcpy(tab->name, name);
	tab->parent=NULL;

	return 0;
}

