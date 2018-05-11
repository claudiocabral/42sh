/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:45:42 by jblazy            #+#    #+#             */
/*   Updated: 2018/04/13 16:46:38 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <mysh.h>

/*
**	heredoc.c
*/
int						check_heredoc(t_prompt *list);

/*
**	interpret_heredoc.c
*/
char					*interpret_heredoc(char *str);

/*
**	heredoc_delim.c
*/
t_prompt				*find_delim(t_prompt *list);
int						list_delim_len(t_prompt *delim);
t_prompt				*cmp_list_delim(t_prompt *list);
t_prompt				*set_delim(t_prompt *list);

/*
**	interpret_heredoc_utils.c
*/
int						delim_len(char *delim);
char					*find_next_delim(char *str, char *delim);
char					*concat_part(char *src, char *begin, char *end);
int						find_begin_heredoc(char *str);
char					*add_heredoc(char *str, char *return_str, char *delim);
#endif
