#ifndef TABLE_H
#define TABLE_H

#include "enums.h"
#include "g_limits.h"
#include "list.h"
#include "blocklist.h"

typedef union {
	int v_int;
	char *v_string;
} value;

typedef struct {
	fieldtype type;
	value val;
} cell;

typedef struct {
	struct table *parent;
	cell *values;
} record;

typedef struct {
	char *name;    /**< The table's name */
	list *fields;  /**< Array of the fields it contains */
	blocklist *records;
	int id;
} table;

table *table_open(const char *name);
int table_close(table *tab);
int table_delete(const table *tab);

bool table_is_open(const char *name);

#endif /* TABLE_H */
