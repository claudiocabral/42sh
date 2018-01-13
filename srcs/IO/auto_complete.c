/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 02:09:29 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <io.h>
#include <dirent.h>
#include <stdlib.h>

int			is_separator(char c)
{
	(void)c;
	return (1);
}

void		auto_complete_push(t_array *array, char *base, char *candidate)
{
	if (ft_strnequ(base, candidate, ft_strlen(base)))
		array_push_back(array, candidate);
}

int			first_word(t_string *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ft_is_whitespace(str->buffer[i]))
		++i;
	while ((unsigned long)i < str->size)
	{
		if (ft_is_whitespace(str->buffer[i]))
			++count;
		if (is_separator(str->buffer[i]))
			count = 0;
	}
	return (!count);
}

int			auto_complete_path(t_array *array, t_terminal *terminal)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str;

	(void)dir;
	(void)entry;
	str = ft_strrchr(terminal->line->buffer, '/');
	*str = 0;
	if (!(dir = opendir(terminal->line->buffer)))
	{
		*str = '/';
		return (0);
	}
	*str = '/';
	while ((entry = readdir(dir)))
		auto_complete_push(array, str + 1, entry->d_name);
	closedir(dir);
	return (1);
}

int			auto_complete_command(t_array *array, t_terminal *terminal)
{
	(void)array;
	(void)terminal;
	return (1);
}

void		choose_possibility(t_array *array, t_terminal *terminail)
{
	void	*it;
}

int			auto_complete(t_terminal *terminal, int c)
{
	t_array			*array;

	(void)c;
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	if (!first_word(terminal->line))
		auto_complete_path(array, terminal);
	else
	{
		if (ft_strchr(terminal->line->buffer, '/'))
			auto_complete_path(array, terminal);
		auto_complete_command(array, terminal);
	}
	choose_possibility(array, terminail);
	array_free(array, &free_wrapper);
	return (1);
}
