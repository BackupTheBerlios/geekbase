#ifndef DB_H
#define DB_H

typedef struct {
	char *location;         /**< path to database */
	enum env_type type;     /**< enviroment type */
	short unsigned ntable;  /**< */
	struct table **table;   /**< */
} env;

#endif /* DB_H */
