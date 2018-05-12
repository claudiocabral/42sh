/*
 * file: walker.c
 * author: iomonad
 */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Find correct shit by reading
 * your fckng pattern
 */
void
find_single_pattern(const char* needle,
					const char *path)
{
	DIR* dir = NULL;
	struct dirent *entry = NULL;

	if ((dir = opendir(path)) != NULL) {
		while ((entry = readdir(dir)) != NULL) {
			if (strstr(entry->d_name, needle) != NULL) {
				printf("Matching patterns: %s\n", entry->d_name);
			}
		}
		closedir(dir);
	}
}
