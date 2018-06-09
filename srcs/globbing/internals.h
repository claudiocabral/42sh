/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 09:36:22 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/09 18:28:05 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNALS_H
# define INTERNALS_H

# include <globbing.h>

# define DOOM "  ."

typedef struct	s_pattern
{
	t_bool		error;
	char		*pattern;
}				t_pattern;

/*
** Flavor reference
** for context parsing
*/

typedef enum	e_flavor
{
	REGULAR = 0,
	PATTERN,
	SENTINELLE
}				t_flavor;

/*
** Simple helper to exceed the
** parameters norm's limit.
*/

typedef struct	s_helper
{
	t_flavor	flavor;
	char		*file_bak;
	t_bool		bottom;
	char		*filename;
	char		*cur_path;
}				t_helper;

/*
** Glob data type for parsing
** subtles informations about
** the matched pattern.
** @desc needle_found current occur
** @desc aref heler reference
** @desc final_list solution of matchs
*/

typedef struct	s_glob
{
	size_t		gl_pathc;
	size_t		gl_offs;
	char		*needle_found;
	char		**gl_pathv;
	t_list		*final_list;
	t_helper	*aref;
}				t_glob;

/*
** Internal functions set that
** doesnt need to be shared for
** the whole project
*/

t_bool			is_dominative(char cursor);
t_bool			is_dirwalk_needed(char cursor);
t_bool			brackets_valid_fmt(char c);
void			wildcard_init(t_bool *status, char **pattern,
					t_bool *ret);
char			*retrieve_last_cur(char *pattern,
					int i, int j);
char			*retrieve_start_cur(char *pattern,
						int i, char *begin);
void			replace_begin(char *begin, t_list *tmp,
						char *prime);
void			pre_init_brackets(t_bool *status, t_bool *ret,
						char **pattern);
t_bool			compute_match_wildcard(t_helper *g, char *str,
					char *pattern, t_list **results);
char			*exec_brackets(char **format, int *err,
						char *mat, int i);
t_bool			match_bracket(t_helper *g, char *s,
						char *pattern, t_list **results);
int				init_brackets_offset(char **pattern, int c,
						int ret, int status);
void			retrieve_brackets_occur(char **pattern, int j);
t_bool			have_valid_context(int err,
						char cursor);
t_bool			compute_match_bracket(t_helper *g, char *s,
						char *pattern, t_list **results);
void			store_result(t_list **lst, char *s,
					t_list *tmp, t_list *add);
char			*create_fullpath(char *local, char *name,
						int j, char *path);
char			*retrieve_valid_path(char *local, char *name,
						int i, int j);
t_bool			pattern_dispatcher(t_helper *g, char *s,
						char *pattern, t_list **results);

/*
** directory.c
*/

void			call_dirwalker_priority(t_helper g, char *pattern,
							t_list **results);
t_bool			call_dirwalker(t_helper g, char *pattern, t_list **results,
							t_list *match);
t_bool			compile_pattern(t_helper *g, char *filename, char *pattern,
							t_list **results);

/*
** patterns.c
*/

int				get_patterns(t_list **patterns, char *pattern);
int				compile_glob_brace(t_list *first, char *begin,
						t_list *tmp, char *prime);

/*
** builder.c
*/

char			*build_result(t_list *results, t_list *tmp, int i, char *ret);
int				compute_globbing(const char *pattern, t_glob *g);

/*
** predicates.c
*/

t_bool			needs_globbing(const char *needle, size_t i);
t_bool			prepare_gbuff(t_helper *gbuff);
t_bool			prepare_glob(t_glob *glob);
char			*strtok_glob(char *str, const char *delim, char *end);

/*
** @reducers.c
*/

void			dot_reduce(t_list **head, const char *origin, t_list *aref);

#endif
