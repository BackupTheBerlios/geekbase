#include "lpr_utils.h"
#include "g_error.h"
#include "list.h"

static void swap(record **r1, record **r2);

void table_sort(table *tab)
{
	int fnum;
	unsigned i, j;
	record *cur, *next;

	fnum = list_count_nodes(tab->fields);
	assert(tab);
	assert(fnum == 7);

	for(i = 0; i < tab->records->blocknum - 1; i++) {
		for(j = i; tab->records->blocknum - 1; j++) {
			cur = blocklist_get_elem(tab->records, j);
			next = blocklist_get_elem(tab->records, j+1);

			assert(cur);
			assert(next);

			if(cur->values[1].val.v_int > next->values[1].val.v_int)
				swap(&cur, &next);
			else if(cur->values[1].val.v_int == next->values[1].val.v_int)
				if(cur->values[2].val.v_int > next->values[2].val.v_int)
					swap(&cur, &next);
		}
	}
}

static void swap(record **r1, record **r2)
{
	record *tmp;

	assert(r1 && *r1);
	assert(r2 && *r2);

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}
