#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include <mysh.h>

// int             print_options(t_array *array, char *line);
void			auto_completion(t_prompt **list);
char			*auto_complete(char *line);
void			auto_complete_push(t_array *array, char *base, char *candidate);
int             print_options(t_array *array, char *line);
DIR             *get_dir(char *path, char **str);
void            search_dir(DIR *dir, char *str, t_array *array);
int             first_word(char *line);
int             is_separator(char c);
void            adjust_terminal(char *line, int nbr_lines);
int             choose_possibility(t_array *array, char *str, char *line);
#endif
