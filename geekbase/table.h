#ifndef TABLE_H
#define TABLE_H

typedef struct {
	char *name;             /**< The table's name */
	struct db *parent;      /**< The table's container */
	struct field **fields;  /**< Array of the fields it contains */
} table;

table *table_open(const char *name, unsigned mode);
int table_delete(const table *tab);

#endif /* TABLE_H */
