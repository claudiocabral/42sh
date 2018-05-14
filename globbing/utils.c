/*
 * file: utils.c
 * author: iomonad
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "globbing.h"

/*
 * Safe pattern path
 * helper
 */

char*
getwpath(const char *wild)
{
	size_t i = strlen(wild) - 1;
	size_t j = 0;
	char magic[MAGIC];

	if (strstr(wild, "/") != NULL) {
		while (wild[i] != '/')
			i--;
		i++;
		while (j < i) {
			magic[j] = wild[j];
			j++;
		}
		return ((magic[0] != '\0') ? strdup(magic) : ".");
	}
	return (strdup("."));
}
