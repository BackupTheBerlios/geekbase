#ifndef TABLE_H
#define TABLE_H

#include "enums.h"
#include "g_limits.h"
#include "list.h"

typedef union {
	int v_int;
	char *v_string;
} value;

typedef struct {
	field_type type;
	value val;
} cell;

typedef struct {
	struct table *parent;
	cell *values;
} record;

typedef struct {
	char *name;    /**< The table's name */
	list *fields;  /**< Array of the fields it contains */
} table;

table *table_open(const char *name);
int table_close(const table *tab);
int table_delete(const table *tab);

bool table_is_open(const char *name);

#endif /* TABLE_H */
