#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "table.h"
#include "field.h"
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
		if(table_exists(name)) {
			tab = table_load(name);
			if(!tab) {
				return NULL;
			}
		} else {
			XMALLOC(tab, sizeof(tab), NULL);
			tab->name = strdup(name);
			tab->records = blocklist_new(25, sizeof(record));
			tab->fields = list_new(sizeof(field));
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

bool
table_exists(const char *name)
{
	char *fullname;
	struct stat st;

	fullname = strdup(dbase->location);
	fullname = strcat(fullname, "/");
	fullname = strcat(fullname, name);
	fullname = strcat(fullname, ".gb");

	if(stat(fullname, &st) == 0)
		return true;
	else
		return false;
}

/* @todo da implementare */
bool
table_is_open(const char *name)
{
	return false;
}
