#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "db.h"
#include "table.h"
#include "field.h"
#include "g_error.h"
#include "utils.h"

static db *dbase = NULL;

static field *parse_field(FILE *fin);
static record *parse_record(FILE *fin, list *fields);
static void eat_spaces(FILE *stream);
static char *chomp(char *s);
static char *g_fgets(char *s, int size, FILE *stream);

int
db_open(const char *location)
{
	assert(location);
	/* env_init can be called only once */
	assert(!db_is_open());

	XMALLOC(dbase, sizeof(dbase), -1);

	dbase->location = strdup(location);
	dbase->dir = opendir(location);
	if (!dbase->dir) {
		g_errno = ERR_WRONG_LOCATION;
		return -1;
	}

	dbase->type = TYPE_DISK;
	dbase->open_tables = list_new(sizeof(table));

	return 0;
}

int
db_close(void)
{
	if(db_is_open()) {
/* 		free(dbase->location); */
		free(dbase->dir);
		list_free(dbase->open_tables);
		free(dbase);
	}
	dbase = NULL;

	return 0;
}

bool
db_is_open(void)
{
	return dbase ? true : false;
}

table*
table_load(const char *name)
{
	char *fullname;
	FILE *file;
	table *tab;
	unsigned maxnamlen;
	int fieldnum;
	int ret, i;
	field *tmpf;
	record *tmpr;
	list *flist;

	assert(name);
	assert(strnlen(name, MAX_TABNAME_LEN+1) < MAX_TABNAME_LEN);

	if (db_is_open()) {
		fullname = strdup(dbase->location);
		fullname = strcat(fullname, "/");
		fullname = strcat(fullname, name);
		fullname = strcat(fullname, ".gb");

		file = fopen(fullname, "r");
		if (!file) {
			set_error(ERR_OPEN_TABLE);
			perror("table_load()");
			free(fullname);
			return NULL;
		}
		free(fullname);

		XMALLOC(tab, sizeof(table), NULL);
		tab->records = blocklist_new(25, sizeof(record));

		/* The number of fields */
		ret = fscanf(file, "%d", &fieldnum);
		/* if wrong character, EOF or wrong fieldnum */
		if (ret <= 0 || fieldnum <= 0) {
			set_error(ERR_INVALID_TABLE);
			return NULL;
		}

		flist = list_new(sizeof(field));
		/* getting field definitions */
		for(i = 0; i < fieldnum; i++) {
			tmpf = parse_field(file);
			if(!tmpf) {
				free(tab);
				list_free(flist);
				return NULL;
			} else {
				list_append(flist, i, tmpf);
			}
		}
		tab->fields = flist;

		/* @todo parse records */
		while(!feof(file)) {
			tmpr = parse_record(file, tab->fields);
			eat_spaces(file);
			if(!tmpr) {
				free(tab);
				free(tab->fields);
				return NULL;
			} else {
				tmpr->parent = tab;
				blocklist_append_elem(tab->records, (void*)tmpr);
			}
		}

		tab->name = strdup(name);

		return tab;
	}

	return NULL;
}

static field*
parse_field(FILE *stream)
{
	field *tmp;
	char *name, *type;
	field_type ty;

	assert(stream);

	XMALLOC(name, MAX_FIELDNAME_LEN+2, NULL);
	g_fgets(name, MAX_FIELDNAME_LEN+2, stream);
	if(strlen(name) > MAX_FIELDNAME_LEN) {
		set_error(ERR_INVALID_TABLE);
		free(name);
		return NULL;
	}

	XMALLOC(type, MAX_TYPENAME_LEN+1, NULL);
	g_fgets(type, MAX_TYPENAME_LEN+1, stream);

	if(!strcmp(type, "int"))
		ty = TYPE_INT;
	else if(!strcmp(type, "string"))
		ty = TYPE_STRING;
	else if(!strcmp(type, "timestamp"))
		ty = TYPE_TIMESTAMP;
	else {
		set_error(ERR_INVALID_TABLE);
		free(name);
		free(type);
		return NULL;
	}

	tmp = field_create(name, ty);
	free(name);
	free(type);

	return tmp;
}

static record*
parse_record(FILE *fin, list *fields)
{
	record *rec;
	cell *cel;
	elem *el;
	field *fi;
	int ret, count = 0;
	char *num;

	assert(fin);
	assert(fields);
	assert(fields->head);

	XMALLOC(rec, sizeof(record), NULL);
	rec->parent = NULL;
	XMALLOC(rec->values, sizeof(cell) * list_count_nodes(fields), NULL);
	XMALLOC(fi, sizeof(field), NULL);

	el = fields->head;
	while(el) {
		fi = el->buf;

		XMALLOC(cel, sizeof(cell), NULL);

		switch(fi->type) {
		case TYPE_INT:
			cel->type = TYPE_INT;
			ret = fscanf(fin, "%d", &cel->val.v_int);
/* 			XMALLOC(num, 256, NULL); */
/* 			num = g_fgets(); */
			/* if wrong character */
			if (ret <= 0) {
				set_error(ERR_INVALID_TABLE);
				free(rec);
				free(rec->values);
				free(cel);
				free(fi);
				return NULL;
			}
			memcpy(&rec->values[count], cel, sizeof(cell));
			break;
		case TYPE_STRING:
			cel->type = TYPE_STRING;
			XMALLOC(cel->val.v_string, MAX_STRING_LEN + 2, NULL);
			eat_spaces(fin);
			cel->val.v_string = fgets(cel->val.v_string, MAX_STRING_LEN + 2, fin);
			chomp(cel->val.v_string);
			if (strlen(cel->val.v_string) > MAX_STRING_LEN) {
				set_error(ERR_INVALID_TABLE);
				free(rec);
				free(rec->values);
				free(cel);
				free(cel->val.v_string);
				free(fi);
				return NULL;
			}
			memcpy(&rec->values[count], cel, sizeof(cell));
			break;
		case TYPE_TIMESTAMP:
			cel->type = TYPE_TIMESTAMP;
			ret = fscanf(fin, "%d", &cel->val.v_int);
			/* if wrong character or negative number */
			if (ret <= 0 || cel->val.v_int < 0) {
				set_error(ERR_INVALID_TABLE);
				free(rec);
				free(rec->values);
				free(cel);
				free(fi);
				return NULL;
			}
			memcpy(&rec->values[count], cel, sizeof(cell));
			break;
		}

		el = el->next;
		++count;
	}

	return rec;
}

static void
eat_spaces(FILE *stream)
{
	int c;

	while(1) {
		c = fgetc(stream);
		if(c == EOF)
			break;
		else if(!isspace(c) && c != '\0') {
			fseek(stream, -1, SEEK_CUR);
			break;
		}
	}
}

static char*
chomp(char *s)
{
	int len;

	len = strlen(s);
	if(s[len-1] == '\n')
		s[len-1] = '\0';

	return s;
}

static char*
g_fgets(char *s, int size, FILE *stream)
{
	int c, offset = -1;

	if (size == 0)
		return s;

	/* eat whitespaces and newlines */
	eat_spaces(stream);

	while(++offset < size) {
		c = fgetc(stream);
		if (c == EOF || isspace(c) || c == '\0')
			break;
		else
			s[offset] = c;
	}
	s[offset] = '\0';

	return s;
}
