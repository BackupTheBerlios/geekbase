#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "db.h"
#include "g_error.h"
#include "utils.h"

static db *dbase = NULL;

/** @todo finirla */
int env_init(const char *location)
{
	DIR *dbdir;

	assert(location);
	/* env_init can be called only once */
	assert(!dbase);

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
	dbase->tables = NULL;

	return 0;
}

/** @todo da implementare */
int env_close(void)
{
	return 0;
}

/** @todo implementarla */
bool db_exists(const char *name)
{
	assert(name);

	return true;
}
