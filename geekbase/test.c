#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db.h"
#include "table.h"
#include "field.h"
#include "cell.h"
#include "g_error.h"

int main() {
	table *tab;
	field **defs;

	if(db_open("db")) {
		g_error("db_open");
		return 1;
	}

	tab = table_open("test");
	if(!tab) {
		g_error("table_open");
		return 1;
	}

	defs = table_get_field_defs(tab);
	while(!table_end(tab)) {
		
	}

	if(db_close()) {
		g_error("db_clos ");
		return 1;
	}

	return 0;
}
