#ifndef FIELD_H
#define FIELD_H

#include "enums.h"
#include "g_error.h"

typedef struct {
	char *name;                  /**<  */
	enum field_type type;        /**<  */
	short unsigned lenght;       /**<  */
	const struct table *parent;  /**<  */
} field;

/**
 * @brief Creates a field.
 * @param name Field name
 * @param type Field type
 * @param length The length of the field
 * @return A pointer to the field just created
 **/
field *field_create(char *name, int type, short unsigned length);

/**
 * @brief Frees a field.
 * @param morituro The field to kill
 **/
void field_free(field *morituro);

/**
 * @brief Edits field.
 * @param fl The field to edit
 * @param name
 * @param length
 * @return 0 if all ok, otherwise -1
 **/
int field_edit(field *fl, char *name, short unsigned length);

#endif /* FIELD_H */
