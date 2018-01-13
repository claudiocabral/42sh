/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 15:26:49 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <io.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int			is_separator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

void		auto_complete_push(t_array *array, char *base, char *candidate)
{
	size_t	ret;

	if (!candidate)
		return ;
	if ((ret = ft_strnequ(base, candidate, ft_strlen(base))))
		ret = (size_t)array_push_back(array, &candidate);
	if (!ret)
		free(candidate);
}

int			first_word(t_string *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while ((unsigned long)i < str->size)
	{
		while (ft_is_whitespace(str->buffer[i]))
			++i;
		while (str->buffer[i] && !ft_is_whitespace(str->buffer[i]))
			++i;
		if (is_separator(str->buffer[i - 1]))
			count = 0;
		else if (str->buffer[i])
			++count;
	}
	return (!count);
}

DIR			*get_dir(char *path, char **str)
{
	DIR		*dir;
	char	*dir_path;
	char	*begin;

	if (!(begin = ft_strrchr(path, ' ')))
		begin = path;
	else
		++begin;
	if ((dir_path = ft_strrchr(begin, '/')))
	{
		*dir_path = 0;
		dir = opendir(begin);
		*dir_path = '/';
		*str = ft_strdup(dir_path + 1);
	}
	else
	{
		dir = opendir(".");
		*str = ft_strdup(begin);
	}
	return (dir);
}

int			is_directory_symlink(struct dirent *entry)
{
	DIR		*dir;
	char	buff[2048];

	if (entry->d_type != DT_LNK)
		return (0);
	readlink(entry->d_name, buff, 2048);
	if (!(dir = opendir(buff)))
		return (0);
	closedir(dir);
	return (1);
}

char		*auto_complete_path(t_array *array, t_terminal *terminal)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str;
	char			*candidate;

	if (!(dir = get_dir(terminal->line->buffer, &str)))
		return (0);
	while ((entry = readdir(dir)))
	{
		if (!(candidate = malloc(sizeof(char)
						* (ft_strlen(entry->d_name) + 2))))
			break ;
		candidate[0] = 0;
		ft_strcat(candidate, entry->d_name);
		if (entry->d_type == DT_DIR || is_directory_symlink(entry))
			ft_strcat(candidate, "/");
		auto_complete_push(array, str, candidate);
	}
	closedir(dir);
	return (str);
}

char		*auto_complete_command(t_array *array, t_terminal *terminal)
{
	(void)array;
	(void)terminal;
	return (0);
}

void		choose_possibility(t_array *array, char *str,
		t_terminal *terminal)
{
	char	**it;

	(void)str;
	(void)terminal;
	it = (char **)array->begin;
}

int			auto_complete(t_terminal *terminal, int c)
{
	t_array			*array;
	char			*str;

	(void)c;
	str = 0;
	if (terminal->line->size == 0)
		return (1);
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	if (!first_word(terminal->line))
		str = auto_complete_path(array, terminal);
	else
	{
		if (ft_strchr(terminal->line->buffer, '/'))
			str = auto_complete_path(array, terminal);
		else
			str = auto_complete_command(array, terminal);
	}
	if (str && array_size(array) == 1)
		terminal_insert_string(terminal,
				*(char **)array->begin + ft_strlen(str));
	else if (str)
		choose_possibility(array, str, terminal);
	free(str);
	array_free(array, (t_freef) &free_wrapper);
	return (1);
}