/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:46:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 16:04:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKTICK_H
# define BACKTICK_H

# include <string.h>

char	*get_back_tick_content(char *str, size_t pos,
							char **start, char **stop);
int		collect_command_output(char *str, int read_write[2]);
char	*command_output_to_string(int read_write[2]);
char	*replace_backtick(char *str, char *new_str, char *begin, char *end);
int		process_input_after_backtick(char *str);
char	*ft_strreplace(char *origin, char *piece, size_t pos, size_t len);
char	*backticks_replace(char *str, size_t pos);

#endif
