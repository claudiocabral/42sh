/*
 * file: globbing.h
 * author: iomonad
 */

#ifndef GLOBBING_H
#define GLOBBING_H

#define DBG(x) (printf("%s, l%d: ", __FILE__, __LINE__); \
				x;)
#define TS_SET " \t\r"
#define INCLUSIVE_SET "*/"
#define SEPARATOR " "
#define MAGIC 0x1000

/*
 * Globbing flavors
 */
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

/*
 * Globing lexer linked
 * list
 */
typedef struct	s_glob {
	char *raw;
	Flavor token;
	struct s_glob *next;
}				t_glob;


char*   deglob(const char *input);
void    append(t_glob** head, t_glob *node);
void    cleanup(t_glob* head);
t_glob* newnode(const char *raw, Flavor flavor);
void    append(t_glob** head, t_glob *node);
void    find_single_pattern(const char *path, char **patterns, char **results);
void    full_inclusive_pattern(const char *path, char **results, size_t i);
char*   getwpath(const char *wild, char *pattern);

#endif /* GLOBBING_H */
