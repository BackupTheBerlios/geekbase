#ifndef ENUMS_H
#define ENUMS_H

/* Enums */
typedef enum {
	TYPE_INT,       /**< field is an integers collector */
	TYPE_STRING,    /**< field is a strings collector */
	TYPE_TIMESTAMP  /**< field is a timestamp (xx:yy:zz) collector */
} fieldtype;

typedef enum {
	TYPE_DISK  /**<  */
} env_type;

typedef enum {
	false,
	true
} bool;

#endif /* ENUMS_H */
