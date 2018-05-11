/*
 * file: globbing.h
 * author: iomonad
 */

#ifndef GLOBBING_H
#define GLOBBING_H

#define DBG(x) (printf("%s, l%d: ", __FILE__, __LINE__); \
				x;)

typedef enum Glob_Flavor {
	INCLUSIVE = 0,				/* * */
	ANYCHAR,					/* ? */
	STRICTARRAY,				/* [abc] */
	ARRAYRANGE,					/* [a-c] */
	STRICTARRAY_NOT,			/* [!abc] */
	ARRAYRANGE_NOT,				/* [!a-c] */
	STRING_MATCHER,				/* {foo,bar} */
	SENTINEL 					/* Not affected reference */
} Flavor;

int deglob(const char *input);

#endif /* GLOBBING_H */
