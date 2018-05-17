/*
 * file: main.c
 * author: iomonad
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

#include <globbing.h>

int
main(int argc, char *argv[])
{
	if (argc == 2 && argv[1][0] != '\0') {
		return (printf("%s\n", deglob(argv[1])));
	}
	return (EXIT_SUCCESS);
}
