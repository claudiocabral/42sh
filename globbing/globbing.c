/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <globbing.h>

int
deglob(const char *input)
{
	int occur = 0;

	if ((occur = strcspn(input, "*"))) {
#ifdef DEBUG
		printf("%s.%d: Got a pattern at %d\n",
			   __FILE__, __LINE__, occur);
#endif
	}
	return (EXIT_SUCCESS);
}
