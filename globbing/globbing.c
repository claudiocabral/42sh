/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <globbing.h>


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

int
deglob(const char *input)
{
	int occur = 0;
	char *tk = strtok(input, " \t\r");

	while (tk != NULL) {
#ifdef DEBUG
		printf("Raw: %s - Token: %d\n", tk, getflavor(tk));
#endif
		tk = strtok(NULL, " \t\r");
	}
	return (EXIT_SUCCESS);
}
