/*
 * file: expanders.h
 * author: iomonad
 */

#ifndef EXPANDERS_H
#define EXPANDERS_H

#include "globbing.h"

char* inclusive_expanders(t_glob *pc);
char* anychar_expanders(t_glob *pc);
char* strictarray_expanders(t_glob *pc);
char* arrayrange_expanders(t_glob *pc);
char* strictarray_not_expanders(t_glob *pc);
char* arrayrange_not_expanders(t_glob *pc);
char* stringmatcher_expanders(t_glob *pc);

typedef struct s_callbacks
{
	Flavor flavor;
	char (*callback)(t_glob*);
} t_callbacks;

t_callbacks	callbacks[SENTINEL + 2] =
{
	{INCLUSIVE, inclusive_expanders},
	{ANYCHAR, anychar_expanders},
	{STRICTARRAY, strictarray_expanders},
	{ARRAYRANGE, arrayrange_expanders},
	{STRICTARRAY_NOT, strictarray_not_expanders},
	{ARRAYRANGE_NOT, arrayrange_not_expanders},
	{STRING_MATCHER, stringmatcher_expanders},
	{SENTINEL, NULL},
	{0}
};

#endif
