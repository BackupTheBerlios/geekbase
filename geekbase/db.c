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
static char *g_fgets(char *s, int size, FILE *stream);

/** @todo finirla */
int db_open(const char *location)
{
	DIR *dbdir;

	assert(location);
	/* env_init can be called only once */
	assert(!db_is_open());

	XMALLOC(dbase, sizeof(dbase), -1);

	strcpy(dbase->location, location);
	dbdir = opendir(location);
	if (!dbdir) {
		g_errno = ERR_WRONG_LOCATION;
		return -1;
	} else {
		dbase->dir = dbdir;
	}

	dbase->type = TYPE_DISK;
	dbase->ntable = 0;
	dbase->open_tables = NULL;

	return 0;
}

/** @todo da finire */
int db_close(void)
{
	if(db_is_open()) {
		free(dbase);
	}
	dbase = NULL;

	return 0;
}

bool db_is_open(void)
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

	assert(name);
	assert(strnlen(name, MAX_TABNAME_LEN+1) < MAX_TABNAME_LEN);

	if (db_is_open()) {
		maxnamlen = strlen(dbase->location) + MAX_TABNAME_LEN + 5;
		XMALLOC(fullname, maxnamlen, NULL);

		strcpy(fullname, dbase->location);
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

		/* The number of fields */
		fscanf(file, "%d", &fieldnum);
		/* if wrong character, EOF or wrong fieldnum */
		if (ret <= 0 || fieldnum <= 0) {
			set_error(ERR_INVALID_TABLE);
			return NULL;
		}

		/* getting field definitions */
		for(i = 0; i < fieldnum; i++) {
			tmpf = parse_field(file);
			if(!tmpf) {
				free(tab);
				return NULL;
			}
		}
		XMALLOC(tab->name, strlen(name), NULL);
		strcpy(tab->name, name);

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

	if(strcmp(type, "int"))
		ty = TYPE_INT;
	else if(strcmp(type, "string"))
		ty = TYPE_STRING;
	else if(strcmp(type, "timestamp"))
		ty = TYPE_TIMESTAMP;
	else {
		set_error(ERR_INVALID_TABLE);
		free(name); free(type);
		return NULL;
	}

	tmp = field_create(name, ty);
	free(name); free(type);

	return tmp;
}

static char*
g_fgets(char *s, int size, FILE *stream)
{
	int c, count = -1;

	if (size == 0)
		return s;

	while(++count < size) {
		c = fgetc(stream);
		if (c == EOF || isspace(c))
			break;
		else
			s[count] = c;
	}
	s[count] = '\0';

	return s;
}
