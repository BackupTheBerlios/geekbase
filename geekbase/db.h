#ifndef DB_H
#define DB_H

#include <sys/types.h>
#include <dirent.h>

#include "enums.h"
#include "blocklist.h"
#include "table.h"

typedef struct {
	char *location;           /**< path to database */
	DIR *dir;                 /**<  */
	env_type type;            /**< enviroment type */
	unsigned ntable;          /**<  */
	blocklist **open_tables;  /**<  */
} db;

int db_open(const char *location);
int db_close(void);
bool db_is_open(void);

table *table_load(const char *name);

#endif /* DB_H */
