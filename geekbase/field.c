#include <string.h>

#include "field.h"
#include "utils.h"
#include "g_limits.h"

field*
field_create(char *name, fieldtype type)
{
	field *temp;
      
	XMALLOC(temp, sizeof(field), NULL); 

	if(strnlen(name, MAX_FIELDNAME_LEN) > MAX_FIELDNAME_LEN) {
		set_error(ERR_INVALID_ARG);
		free(temp);
		return NULL;
	} else {
		temp->name = strdup(name);
	}
	temp->type = type;
	temp->parent = NULL;

	return temp;
}

void
field_free(field *morituro)
{
	assert(morituro && morituro->name);

	free(morituro->name);
	free(morituro); 
}
