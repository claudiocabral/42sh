/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <libft.h>
#include <sys/types.h>

#include "globbing.h"

/*
 * Return function wrapper
 * for the runner middleware.
 */
char	*deglob(const char *input)
{
	return (((char*)input));
}
