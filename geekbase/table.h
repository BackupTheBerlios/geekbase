#ifndef TABLE_H
#define TABLE_H

#include "enums.h"
#include "g_limits.h"

typedef struct {
	char *name;             /**< The table's name */
	struct field **fields;  /**< Array of the fields it contains */
} table;

table *table_open(const char *name);
int table_delete(const table *tab);

bool table_is_open(const char *name);

#endif /* TABLE_H */
