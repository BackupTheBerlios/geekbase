#include <string.h>

#include "table.h"
#include "db.h"
#include "g_error.h"
#include "g_limits.h"
#include "utils.h"

table*
table_open(const char *name)
{
	table *tab;

	assert(name);

	if(!table_is_open(name)) {
		XMALLOC(tab, sizeof(table), NULL);
		XMALLOC(tab->name, strlen(name), NULL);
		strcpy(tab->name, name);
		return tab;
	} else {
		g_errno = ERR_TABLE_EXISTS;
		return NULL;
	}
}

/* @todo da implementare */
int
table_close(const table *tab)
{
	return 0;
}

/* @todo da implementare */
int
table_delete(const table *tab)
{
	return 0;
}

/* @todo da implementare */
bool
table_is_open(const char *name)
{
	return false;
}
