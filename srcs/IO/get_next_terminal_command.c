/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:53:37 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/21 20:04:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_string.h>

int		is_open_bracket(char c)
{
	return (c == '\"' || c == '\'' || c == '{' || c == '[' || c == '(');
}

char	get_closing_bracket(char c)
{
	if (c == '\"' || c == '\'')
		return (c);
	else if (c == '[')
		return (']');
	else if (c == '{')
		return ('}');
	else if (c == '(')
		return (')');
	else
		return (0);
}

int		escape_string(char buffer[2048], int begin, t_string *str)
{
	if (buffer[begin] == '\\' && buffer[begin + 1])
	{
		++begin;
		string_append_char(str, buffer[begin]);
		return (begin);
	}
	return (begin);
}

int		get_next_bracket(char buffer[2048], int begin, t_string *str)
{
	char	c;

	c = get_closing_bracket(buffer[begin]);
	while (buffer[begin])
	{
		string_append_char(str, buffer[begin]);
		if (buffer[begin] == c)
			return (begin + 1);
		begin = escape_string(buffer, begin, str) + 1;
	}
	return (begin);
}

int		get_command(char buffer[2048], int begin, t_string *str)
{
	while (buffer[begin])
	{
		string_append_char(str, buffer[begin]);
		if (buffer[begin] == '\n')
			return (begin + 1);
		else if (is_open_bracket(buffer[begin]))
			begin = get_next_bracket(buffer, begin, str);
		begin = escape_string(buffer, begin, str) + 1;
	}
	return (begin);
}

int		get_next_terminal_command(int fd, t_string *str)
{
	static char	buffer[2048] = {0};
	static int	begin = 0;

	if (buffer[begin] && (begin = get_command(buffer, begin, str)))
		return (1);
	while((begin = read(fd, buffer, 2047)) > 0)
	{
		buffer[begin] = 0;
		begin = 0;
		while (buffer[begin])
		{
			begin = get_command(buffer, begin, str);
		}
	}
	return (0);
}
