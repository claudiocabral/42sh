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
getwpath(const char *wild, char *pattern)
{
	size_t i = strlen(wild) - 1;
	size_t j = 0, k = 0;
	char magic[MAGIC];
	char tmp[MAGIC];

	if (strstr(wild, "/") != NULL) {
		while (wild[i] != '/')
			i--;
		i++;
		k = i;
		while (wild[k] != '\0') {
			tmp[j] = wild[k];
			k++;
			j++;
		}
		pattern = strdup(tmp);
		j = 0;
		while (j < i) {
			magic[j] = wild[j];
			j++;
		}
		return (strdup(magic));
	}
	return (strdup("."));
}
