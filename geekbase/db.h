#ifndef DB_H
#define DB_H

#include <sys/types.h>
#include <dirent.h>

#include "enums.h"
#include "blocklist.h"

typedef struct {
	char *location;      /**< path to database */
	DIR *dir;            /**<  */
	env_type type;       /**< enviroment type */
	unsigned ntable;     /**<  */
	blocklist **tables;  /**<  */
} db;

int env_init(const char *location);
int env_close(void);
bool db_exists(const char *name);

#endif /* DB_H */
