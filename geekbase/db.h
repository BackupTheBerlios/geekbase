#ifndef DB_H
#define DB_H

#include <sys/types.h>
#include <dirent.h>

#include "enums.h"
#include "table.h"
#include "list.h"

typedef struct {
	char *location;     /**< path to database */
	DIR *dir;           /**<  */
	env_type type;      /**< enviroment type */
	list *open_tables;  /**<  */
} db;

int db_open(const char *location);
int db_close(void);
bool db_is_open(void);

table *table_load(const char *name);
int table_save(table *tab);

#endif /* DB_H */
