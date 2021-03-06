/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 11:54:39 by mprevot           #+#    #+#             */
/*   Updated: 2018/06/10 11:54:43 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include <mysh.h>

typedef struct		s_autocompl {
	char			*str;
	int				cursor;
}					t_autocompl;

typedef struct		s_infocompl {
	int				size;
	int				width;
	int				height;
	int				col;
	int				row;
	unsigned int	max_size;
	int				display_start;
	int				display_end;
	char			*str;
	t_autocompl		*array;
}					t_infocompl;

void				auto_completion(t_prompt **list);
char				*auto_complete(char *line);
int					print_options(t_array *array, char *line);
DIR					*get_dir(char *path, char **str);
void				search_dir(DIR *dir, char *str, t_array *array);
int					first_word(char *line);
int					is_separator(char c);

void				input_autocompletion(
	char *input, t_prompt **list, t_infocompl *info);

void				choose_possibility(t_array *array, char *str);
void				display_completion(t_infocompl *info);
void				auto_complete_push(
	t_array *array, char *base, char *candidate);

void				search_builtins(char *str, t_array *array);
void				sort_possibilites(t_autocompl *pos, t_infocompl *info);
void				free_autocompletion(t_sh *sh);

void				add_complete(t_prompt **list, char *to_add);

void				move_left_autocompl(t_autocompl *possibilities,
					t_infocompl *info);
void				move_right_autocompl(t_autocompl *possibilities,
					t_infocompl *info);
void				move_up_autocompl(t_autocompl *possibilities,
					t_infocompl *info);
void				move_down_autocompl(t_autocompl *possibilities,
					t_infocompl *info);

#endif
