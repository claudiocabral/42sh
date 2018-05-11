/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <globbing.h>

int
deglob(const char *input)
{
#ifdef DEBUG
	printf("Deglobbing: \"%s\"\n", input);
#endif
	return (EXIT_SUCCESS);
}
