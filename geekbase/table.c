#include <string.h>

#define _IMPL_

#include "table.h"
#include "g_error.h"
#include "utils.h"

table*
table_create (char *name)
{
	table *tab;

	assert(name);

	XMALLOC(tab, sizeof(table), NULL);
	XMALLOC(tab->name, strlen(name), NULL);
	strcpy(tab->name, name);
	tab->parent = NULL;

	return tab;
}

