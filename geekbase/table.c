#include <string.h>

#include "table.h"
#include "db.h"
#include "g_error.h"
#include "g_limits.h"
#include "utils.h"

extern db *dbase;
extern unsigned num_tables;
extern unsigned idmin;

table*
table_open(const char *name)
{
	table *tab;

	assert(name);

	if(!table_is_open(name)) {
		tab = table_load(name);
		if(!tab) {
			return NULL;
		}
		tab->id = idmin;
		list_insert(dbase->open_tables, tab->id, (void*)tab);
		++idmin;
		++num_tables;
		return tab;
	} else {
		g_errno = ERR_TABLE_EXISTS;
		return NULL;
	}
}

int
table_close(table *tab)
{
	assert(tab);

	if(table_is_open(tab->name)) {
		table_save(tab);
		list_del_node(dbase->open_tables, tab->id);
		--num_tables;
	}

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
