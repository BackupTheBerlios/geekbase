#include <stdlib.h> 
#include <stdio.h> 

#ifndef GEEKBASE_H
#define GEEKBASE_H

#include "enums.h"
#include "table.h"

typedef struct {
	char *name;          /**< path to database pool */
	enum env_type type;  /**< enviroment type */
} env;

typedef struct {
	char *name;             /**<  */
	short unsigned ntable;  /**<  */
	struct env *parent;     /**<  */
	struct table **table;   /**<  */
} db;

#endif /* GEEKBASE_H */
