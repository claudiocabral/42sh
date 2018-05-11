/*
 * file: globbing.h
 * author: iomonad
 */

#ifndef GLOBBING_H
#define GLOBBING_H

#define DBG(x) (printf("%s, l%d: ", __FILE__, __LINE__); \
				x;)

int deglob(const char *input);

#endif /* GLOBBING_H */
