/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:16:02 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 18:11:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <ft_string.h>
#include <ft_printf.h>
#include <environment.h>

t_string const	*set_oldpwd(char const *str)
{
	static t_string	*path = 0;

	if (path == 0)
		path = string_create(32);
	if (!str)
		return (path);
	string_clear(path);
	string_append(path, str);
	if (ft_setenv("OLDPWD", path->buffer, 1) != 0)
		ft_dprintf(2, "cd: failed to updated PWD\n");
	return (path);
}

t_string const	*set_pwd(char const *str)
{
	static t_string	*path = 0;

	if (path == 0)
		path = string_create(32);
	if (!str)
		return (path);
	set_oldpwd(path->buffer);
	string_clear(path);
	string_append(path, str);
	if (ft_setenv("PWD", path->buffer, 1) != 0)
		ft_dprintf(2, "cd: failed to updated PWD\n");
	return (path);
}

int				remove_previous_path(t_string *path, int pos)
{
	char	*begin;
	int		tmp;

	tmp = path->buffer[pos];
	path->buffer[pos] = 0;
	begin = ft_strrchr(path->buffer, '/');
	if (!begin)
	{
		path->buffer[pos] = tmp;
		return (0);
	}
	path->buffer[pos] = tmp;
	string_delete_n(path, begin - path->buffer,
			pos - (begin - path->buffer) + 3);
	return (1);
}

int				clean_back_path(t_string *path)
{
	int		pos;

	while ((pos = string_find(path, "../")) >= 0)
	{
		if (!remove_previous_path(path, pos))
			return (0);
	}
	if (path->size > 2 && ft_strequ(path->buffer + path->size - 3, "/.."))
	{
		if (!remove_previous_path(path, path->size - 3))
			return (0);
	}
	if (path->size > 2 && ft_strequ(path->buffer + path->size - 2, "/."))
		string_delete_n(path, path->size - 2, 2);
	if (path->size > 1 && path->buffer[path->size - 1] == '/')
		string_delete(path, path->size - 1);
	if (path->size == 0)
		return (0);
	return (1);
}

t_string		*clean_path(char *path)
{
	t_string		*str;
	t_string const	*pwd;

	ZERO_IF_FAIL(str = string_create(ft_strlen(path)));
	pwd = set_pwd(0);
	if (path[0] != '/')
	{
		string_append(str, pwd->buffer);
	}
	string_append(str, "/");
	string_append(str, path);
	if (str->buffer[str->size - 1] == '/')
		string_delete(str, str->size -1);
	string_replace(str, "//", "/");
	string_replace(str, "./", "");
	if (!clean_back_path(str))
	{
		ft_dprintf(2, "cd: Error: invalid path\n");
		return (0);
	}
	string_replace(str, "//", "/");
	return (str);
}
