#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mcheck.h>

#include "db.h"
#include "table.h"
#include "field.h"
#include "g_error.h"

extern db *dbase;

int main() {
	table *tab;
	list *li;
	field *fi;
	record *rec = NULL;
	int i, j = 0, num;
	char c;

	mtrace();

	if(db_open(".")) {
		g_error("db_open");
		return 1;
	}

	printf("1. Visualizza\n2. Creazione e inserimento\n");
	c = getchar();
/* 	c = '2'; */
	switch(c) {
	case '1':
		tab = table_open("nuovo");
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
		break;
	case '2':
		if(table_exists("nuovo"))
			exit(1);
		tab = table_open("nuovo");
		
		fi = field_create("ID", TYPE_INT);
		list_insert(tab->fields, 0, fi);
		fi = field_create("Materia", TYPE_STRING);
		list_insert(tab->fields, 1, fi);
		fi = field_create("Giorno", TYPE_INT);
		list_insert(tab->fields, 2, fi);
		fi = field_create("Aula", TYPE_STRING);
		list_insert(tab->fields, 3, fi);
		fi = field_create("Inizio", TYPE_INT);
		list_insert(tab->fields, 4, fi);
		fi = field_create("Fine", TYPE_INT);
		list_insert(tab->fields, 5, fi);
		fi = field_create("Docente", TYPE_STRING);
		list_insert(tab->fields, 6, fi);

		rec = malloc(sizeof(record));
		rec->parent = tab;
		rec->values = malloc(7 * sizeof(cell));

		rec->values[0].type = TYPE_INT;
		rec->values[0].val.v_int = 0;

		rec->values[1].type = TYPE_STRING;
		rec->values[1].val.v_string = malloc(strlen("Reti logiche"));
		strcpy(rec->values[1].val.v_string, "Reti logiche");

		rec->values[2].type = TYPE_INT;
		rec->values[2].val.v_int = 0;

		rec->values[3].type = TYPE_STRING;
		rec->values[3].val.v_string = malloc(strlen("T8"));
		strcpy(rec->values[3].val.v_string, "T8");

		rec->values[4].type = TYPE_INT;
		rec->values[4].val.v_int = 9;

		rec->values[5].type = TYPE_INT;
		rec->values[5].val.v_int = 11;

		rec->values[6].type = TYPE_STRING;
		rec->values[6].val.v_string = malloc(strlen("Varricchio"));
		strcpy(rec->values[6].val.v_string, "Varricchio");

		blocklist_append_elem(tab->records, (void*)rec);
		table_save(tab);

		break;
	}

	if(db_close()) {
		g_error("db_close()");
		return 1;
	}

	return 0;
}
