#include <string.h>

#include "table.h"
#include "db.h"
#include "g_error.h"
#include "utils.h"

table*
table_open(const char *name, unsigned mode)
{
	table *tab;

	assert(name);

	if(!db_exists(name)) {
		XMALLOC(tab, sizeof(table), NULL);
		XMALLOC(tab->name, strlen(name), NULL);
		strcpy(tab->name, name);
		tab->parent = NULL;
		return tab;
	} else {
		g_errno = ERR_TABLE_EXISTS;
		return NULL;
	}
}

int
table_delete(const table *tab)
{
	return 0;
}
