#ifndef TABLE_H
#define TABLE_H

typedef struct {
	char *name;             /**< The table's name */
	struct db *parent;      /**< The table's container */
	struct field **fields;  /**< Array of the fields it contains */
} table;

table* table_create(char *name);
int table_delete(char *name);

#endif /* TABLE_H */
