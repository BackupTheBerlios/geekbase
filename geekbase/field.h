#ifndef FIELD_H
#define FIELD_H

#include "geekbase.h"

/**
 * @brief Creates a field.
 * @param name Field name
 * @param field_type Field type
 * @param field_type 
 * @return A pointer to the field just created
 */
field *field_create(char *name, enum field_type type, short unigned lenght);

/**
 * @brief Frees a field.
 * @param field The field to kill
 */
void field_free(field *morituro);

/**
 * @brief Edits field.
 * @param name Field name
 * @param field_type Field type
 * @param field_type 
 * @return A pointer to the field just created
 */
int field_edit(field *fl,char *name, short unsigned lenght);

#endif /* FIELD_H */
