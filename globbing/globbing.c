/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "globbing.h"
#include "expanders.h"

/*
 * Trivial lexer for trivial
 * structure parsing
 */
static Flavor
getflavor(const char *prop)
{
	assert(prop != NULL);

	if (strchr(prop, 0x2a)) {
		return (INCLUSIVE);
	} else if (strchr(prop, 0x3f)) {
		return (ANYCHAR);
	} else if ((strchr(prop, 0x5b)
				&& strchr(prop, 0x5d))
			   && strchr(prop, 0x2d) == NULL
			   && strchr(prop, 0x21) == NULL) {
		return (STRICTARRAY);
	} else if ((strchr(prop, 0x5b)
				&& strchr(prop, 0x5d))
			   && strchr(prop, 0x2d)
			   && strchr(prop, 0x21) == NULL) {
		return (ARRAYRANGE);
	} else if ((strchr(prop, 0x5b)
			   && strchr(prop, 0x5d))
			   && strchr(prop, 0x2d) == NULL
			   && strchr(prop, 0x21)) {
		return (STRICTARRAY_NOT);
	} else if ((strchr(prop, 0x5b)
				&& strchr(prop, 0x5d))
			   && strchr(prop, 0x2d)
			   && strchr(prop, 0x21)) {
		return (ARRAYRANGE_NOT);
	} else if ((strchr(prop, 0x7b)
				&& strchr(prop, 0x7d))) {
		return (STRING_MATCHER);
	} else {
		return (SENTINEL);
	}
}

static char*
debugflavor(Flavor flavor)
{
	char *reference[SENTINEL + 1]
		= {"INCLUSIVE",
		   "ANYCHAR",
		   "STRICTARRAY",
		   "ARRAYRANGE",
		   "STRICTARRAY_NOT",
		   "ARRAYRANGE_NOT",
		   "STRING_MATCHER",
		   "SENTINEL"};
	return (reference[flavor]);
}

/*
 * Return the final string
 */
static char*
flatten(t_glob *globs)
{
	char deglob[MAGIC];
	char *temp = NULL;

	assert(globs != NULL);
	while (globs != NULL)
	{
		/*
		 * Flavor assignation
		 * block ~
		 */
		if (globs->token == INCLUSIVE)
			temp = inclusive_expanders(globs);
		else if (globs->token == ANYCHAR)
			temp = anychar_expanders(globs);
		else if (globs->token == STRICTARRAY)
			temp = strictarray_expanders(globs);
		else if (globs->token == ARRAYRANGE)
			temp = arrayrange_expanders(globs);
		else if (globs->token == STRICTARRAY_NOT)
			temp = arrayrange_not_expanders(globs);
		else if (globs->token == ARRAYRANGE_NOT)
			temp = arrayrange_not_expanders(globs);
		else if (globs->token == STRING_MATCHER)
			temp = stringmatcher_expanders(globs);

		/*
		 * String crafting block
		 */
		if (globs->token != SENTINEL
			&& (temp == NULL || temp[0] == '\0')) {
			dprintf(2, "42sh: no matches found for %s token.\n",
					debugflavor(globs->token));
			return (NULL);
		}
		(globs->token != SENTINEL) ? strncat(deglob, temp, strlen(temp))
			: strncat(deglob, globs->raw, strlen(globs->raw));
		(globs->next != NULL) ? strncat(deglob, " ", 1)
			: 0x0;
		globs = globs->next;
	}
	return (strdup(deglob));
}

/*
 * Return function wrapper
 * for the runner middleware.
 */
char*
deglob(const char *input)
{
	char *tk = NULL;
	t_glob *globs = NULL;
	char *deglobbed = NULL;

	tk = strtok((char*)input, TS_SET);
	while (tk != NULL) {
#ifdef DEBUG
		printf("Raw: %s - Token: %s\n",
			   tk, debugflavor(getflavor(tk)));
#endif
		append(&globs, newnode(tk, getflavor(tk)));
		tk = strtok(NULL, TS_SET);
	}
	if ((deglobbed = flatten(globs)) == NULL) {
		cleanup(globs);
		exit(EXIT_FAILURE);
	}
	cleanup(globs);
	return (deglobbed);
}
