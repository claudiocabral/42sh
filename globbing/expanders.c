/*
 * file: expanders.c
 * author: iomonad
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "globbing.h"

/*
 * Process INCLUSIVE token
 */

char*
inclusive_expanders(t_glob *pc)
{
	char patterns[0x32];
	char *tok;
	size_t i = 0;

	/* handle full cases */
	if (strcmp(pc->raw, "*") == 0) {
		full_inclusive_pattern(".");
		return (pc->raw);
	}

	tok = strtok(pc->raw, "*");
	while (tok != NULL) {
		/*
		 *  Gestion des multimatch et
		 * choix entre les logiques.
		 */
		patterns[i] = tok;
		tok = strtok(NULL, "*");
		i++;
	}
	return (pc->raw);
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
