/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 16:17:00 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>
#include <globbing.h>
#include <ft_printf.h>
#include <libft.h>
#include <backtick.h>

int			process_input_after_backtick(char *str)
{
	int		return_value;
	char	*input;

	str = alias_replace(str);
	if ((input = deglob(str, NULL, NULL, NULL)) == NULL)
	{
		free(str);
		return (ft_printf("42sh: No matchs found.\n"));
	}
	input = alias_replace((char *)input);
	return_value = execute(parse(lex(input)));
	str ? ft_strdel(&str) : 0;
	input ? free(input) : 0;
	return (return_value);
}

char		*ft_strreplace(char *origin, char *piece, size_t pos, size_t len)
{
	char *debut;
	char *millieu;
	char *fin;
	char *total;

	debut = ft_memdup(origin, pos);
	millieu = piece;
	fin = ft_strdup(origin + len + 1);
	total = ft_vjoin(3, debut, millieu, fin);
	free(debut);
	free(fin);
	return (total);
}

void		dellines(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}

char		*backticks_replace(char *str, size_t pos)
{
	char	*exec;
	int		read_write[2];
	char	*new_str;
	char	*begin;
	char	*end;

	if (!(exec = get_back_tick_content(str, pos, &begin, &end)))
		return (str);
	if (!(collect_command_output(exec, read_write)))
	{
		free(exec);
		return (str);
	}
	new_str = command_output_to_string(read_write);
	dellines(new_str);
	return (replace_backtick(str, new_str, begin, end));
}

int			process_input(char *str)
{
	return (process_input_after_backtick(backticks_replace(str, 0)));
}
