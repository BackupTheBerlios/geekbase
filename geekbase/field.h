#ifndef FIELD_H
#define FIELD_H

#include "enums.h"
#include "g_error.h"

typedef struct {
	char *name;            /**<  */
	fieldtype type;       /**<  */
	struct table *parent;  /**<  */
} field;

/**
 * @brief Creates a field.
 * @param name Field name
 * @param type Field type
 * @return A pointer to the field just created
 **/
field *field_create(char *name, fieldtype type);

/**
 * @brief Frees a field.
 * @param morituro The field to kill
 **/
void field_free(field *morituro);

#endif /* FIELD_H */
