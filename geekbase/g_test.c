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
	list *li;
	field *fi;
	record *rec = NULL;
	int i, j = 0, num;

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

	/* the number of fields */
	num = list_count_nodes(tab->fields);

	li = tab->fields;
	for(i = 0; i < num; i++) {
		fi = list_search(li, i);
		printf("%s\t", fi->name);
	}
	printf("\n-------------\n");

	rec = blocklist_get_elem(tab->records, j);
	while(rec) {
		for(i = 0; i < num; i++) {
			switch(rec->values[i].type) {
			case TYPE_INT:
			case TYPE_TIMESTAMP:
				printf("%d\t", rec->values[i].val.v_int);
				break;
			case TYPE_STRING:
				printf("%s\t", rec->values[i].val.v_string);
				break;
			}
		}
		printf("\n");
		rec = blocklist_get_elem(tab->records, ++j);
	}

	if(db_close()) {
		g_error("db_close()");
		return 1;
	}

	return 0;
}
