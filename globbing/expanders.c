/*
 * file: expanders.c
 * author: iomonad
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "globbing.h"

/*
 * Process INCLUSIVE token
 */

char*
inclusive_expanders(t_glob *pc)
{
	char *patterns[0x32];
	char *results[MAGIC];
	char *tok;
	char final[MAGIC];
	size_t i = 0;

	assert(pc != NULL);
	if (strcmp(pc->raw, "*") == 0)
		full_inclusive_pattern(".", results, 0);
	else {
		tok = strtok(pc->raw, "*");
		while (tok != NULL) {
			patterns[i] = tok;
			tok = strtok(NULL, "*");
			i++;
		}
		find_single_pattern(".", patterns, results);
		i = 0;
	}
	while (results[i] != NULL) {
		strncat(final, results[i], strlen(results[i]));
		if (results[i + 1] != NULL) {
			strncat(final, " ", 1);
		}
		i++;
	}
	return (strdup(final));
}

/*
 * Process ANYCHAR token
 */
char*
anychar_expanders(t_glob *pc)
{
	return (pc->raw);
}

/*
 * Process STRICARRAY token
 */
char*
strictarray_expanders(t_glob *pc)
{
	return (pc->raw);
}

/*
 * Process ARRAYRANGE token
 */
char*
arrayrange_expanders(t_glob *pc)
{
	return (pc->raw);
}

/*
 * Process STRICTARRAY_NOT token
 */
char*
strictarray_not_expanders(t_glob *pc)
{
	return (pc->raw);
}

/*
 * Process ARRAYRANGE_NOT token
 */
char*
arrayrange_not_expanders(t_glob *pc)
{
	return (pc->raw);
}

/*
 * Process STRINGMATCHER token
 */
char*
stringmatcher_expanders(t_glob *pc)
{
	return (pc->raw);
}
