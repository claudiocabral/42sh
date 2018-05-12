/*
 * file: linked.h
 * author: iomonad
 */

#ifndef LINKED_H
#define LINKED_H

#include "globbing.h"

/*
 * Globing lexer linked
 * list
 */
typedef struct	s_glob {
	char *raw;
	Flavor token;
	struct s_glob *next;
}				t_glob;

t_glob* newnode(const char *raw, Flavor flavor);
void    append(t_glob** head, t_glob *node);

#endif /* LINKED_H */
