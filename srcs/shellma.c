/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/12 03:07:08 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>
#include <globbing.h>
#include <ft_printf.h>
#include <libft.h>
#include <backtick.h>
#include <lexer.h>

int			process_input_after_backtick(char *str)
{
	int		return_value;
	char	*input;
	char const *heredoc;
	char		*exp_heredoc;
	char	*line;

	heredoc = lex_get_heredoc_pointer(str);
	exp_heredoc = NULL;
	if (ft_isprint(*heredoc))
	{
		exp_heredoc = heredoc_token_var(ft_strdup((char *)heredoc));
		line = ft_strndup(str, heredoc - str);
	}
	else
		line = ft_strdup(str);
	if ((input = deglob(line, NULL, NULL, malloc(1))) == NULL)
	{
		free(line);
		return (ft_printf("42sh: No matchs found.\n"));
	}
	free(line);
	line = ft_vjoin(2, input, exp_heredoc ? exp_heredoc : heredoc);
	return_value = execute(parse(lex(line)));
	exp_heredoc ? free(exp_heredoc) : 0;
	str ? ft_strdel(&str) : 0;
	input ? free(input) : 0;
	line ? free(line) : 0;
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
	while (*str)
	{
		if (*str == '\n')
			*str = ' ';
		str++;
	}
}

char		*backticks_replace(char *str, size_t pos)
{
	char	*exec;
	int		read_write[2];
	char	*new_str;
	char	*begin;
	char	*end;

	str = alias_replace(str);
	if (!(exec = get_back_tick_content(str, pos, &begin, &end)))
		return (str);
	dellines(exec);
	exec = alias_replace(exec);
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
