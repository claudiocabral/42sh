/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:05:25 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/16 15:23:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

int			is_separator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

int			first_word(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = -1;
	while ((unsigned long)i < ft_strlen(str))
	{
		++count;
		while (ft_is_whitespace(str[i]))
			++i;
		while (str[i] && !ft_is_whitespace(str[i]))
		{
			++i;
			if (is_separator(str[i - 1]))
				count = -1;
		}
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
		if (dir_path == begin)
			begin = "/";
		else
			dir_path[0] = 0;
		dir = opendir(begin);
		*dir_path = '/';
		*str = ft_strdup(dir_path + 1);
	}
	else
	{
		dir = opendir(".");
		*str = ft_strdup(begin);
	}
	ft_printf("STR = %s\n", *str);
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

void		search_dir(DIR *dir, char *str, t_array *array)
{
	char			*candidate;
	struct dirent	*entry;

	entry = readdir(dir);
	if (ft_strequ(entry->d_name, "."))
		entry = readdir(dir);
	if (ft_strequ(entry->d_name, ".."))
		entry = readdir(dir);
	while (entry)
	{
		if (!(candidate = malloc(sizeof(char)
						* (ft_strlen(entry->d_name) + 2))))
			break ;
		candidate[0] = 0;
		ft_strcat(candidate, entry->d_name);
		if (entry->d_type == DT_DIR || is_directory_symlink(entry))
			ft_strcat(candidate, "/");
		auto_complete_push(array, str, candidate);
		entry = readdir(dir);
	}
	closedir(dir);
}
