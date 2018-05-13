/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <globbing.h>

int
main(int argc, char *argv[])
{
	if (argc == 2) {
		return (printf("%s\n", deglob(argv[1])));
	}
	return (EXIT_SUCCESS);
}
