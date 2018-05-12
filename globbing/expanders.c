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
	char *tok = strtok(pc->raw, "*");
	/*
	 * Todo: Support list combinaison ...
	 */
	if (pc->raw[0] == '*' || pc->raw[strlen(pc->raw)] == '*') {
		printf("uochurcoeducoeu\n");
	}
	while (tok != NULL) {
		find_single_pattern(tok, ".");
		tok = strtok(NULL, "*");
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
