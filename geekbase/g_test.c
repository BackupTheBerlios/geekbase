#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mcheck.h>

#include "db.h"
#include "table.h"
#include "field.h"
#include "g_error.h"

int main() {
	table *tab;
	field **defs;

	mtrace();

	if(db_open(".")) {
		g_error("db_open");
		return 1;
	}

	tab = table_load("table");
	if(!tab) {
		g_error("table_open");
		return 1;
	}

/* 	defs = table_get_field_defs(tab); */
/* 	while(!table_end(tab)) { */
		
/* 	} */

	if(db_close()) {
		g_error("db_close()");
		return 1;
	}

	return 0;
}
