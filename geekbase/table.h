#ifndef TABLE_H
#define TABLE_H

typedef struct {
	char *name;             /**<  */
	struct db *parent;      /**<  */
	struct field **fields;  /**< Array of the fields it contains */
} table;

int table_create(char *name, table *tab);

#endif /* TABLE_H */
