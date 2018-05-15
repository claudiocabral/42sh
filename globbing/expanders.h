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

#endif
