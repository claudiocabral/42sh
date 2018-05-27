#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include <mysh.h>

typedef struct	s_autocompl {
	char		*str;
	int			cursor;
}				t_autocompl;

typedef struct 		s_infocompl {
	int				size;
	int 			width;
	int				col;
	int				row;
	unsigned int 	max_size;
	char			*str;
	t_autocompl		*array;
}					t_infocompl;

void			auto_completion(t_prompt **list);
char			*auto_complete(char *line);
int             print_options(t_array *array, char *line);
DIR             *get_dir(char *path, char **str);
void            search_dir(DIR *dir, char *str, t_array *array);
int             first_word(char *line);
int             is_separator(char c);

void			input_autocompletion(char *input, t_prompt **list, t_infocompl *info);

char			*choose_possibility(t_array *array, char *str);
void			sort_possibilites(t_autocompl *pos, t_infocompl *info);
void			display_completion(t_infocompl *info);
void		auto_complete_push(t_array *array, char *base, char *candidate);
#endif
