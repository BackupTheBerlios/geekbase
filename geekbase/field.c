#include "field.h"
#include "utils.h"

field *
field_create(char *name, int field_type, short unsigned lenght)
{
	field *temp;
      
	XMALLOC(temp, sizeof(field), NULL); 

	temp->name=name;
	temp->type=field_type;
	temp->lenght=lenght;

	return temp;
}

void
field_free(field *morituro)
{
	if(!morituro)
		return;
	free(morituro); 
}

/**
 * Note: it's impossible to edit field type.
 * This because we can't convert points from a type to another.
 */
int
field_edit(field *fl, char *name, short unsigned lenght)
{
	if(!fl)
		return -1;
	fl->name=name;
	fl->lenght=lenght;

	return 0;
}
