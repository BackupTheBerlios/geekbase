#include <stdlib.h> 
#include <stdio.h> 

#ifndef GEEKBASE_H
#define GEEKBASE_H

#include "utils.h"

extern unsigned geek_errno;

/* Enums */
enum field_type {
	TYPE_INT,       /**< field is an integers collector */
	TYPE_STRING,    /**< field is a strings collector */
	TYPE_TIMESTAMP  /**< field is a timestamp (xx:yy:zz) collector */
};

enum env_type {
	TYPE_DISK  /**<  */
};


/* Structs */
typedef struct {
	char *name;            /**<  */
	enum field_type type;   /**<  */
	short unsigned lenght;  /**<  */
	struct table *parent;  /**<  */
} field;

typedef struct {
	char *name;             /**<  */
	struct db *parent;      /**<  */
	struct field **fields;  /**< Array of the fields it contains */
} table;

typedef struct {
	char *name;
	short unsigned ntable;
	struct env *parent;
	struct table **table;
} db;

typedef struct {
	char *name;         /**< path to database pool */
	enum env_type type;  /**< enviroment type */
} env;

#endif /* GEEKBASE_H */
