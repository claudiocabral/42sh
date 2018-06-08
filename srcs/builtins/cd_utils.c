/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:16:02 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/08 18:01:15 by gfloure          ###   ########.fr       */
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

	if (path == 0 && !(path = string_create(32)))
		return (0);
	if (!str)
		return (path);
	string_clear(path);
	if (!string_append(path, str))
		return (0);
	if (ft_setenv("OLDPWD", path->buffer, 1) != 0)
	{
		ft_dprintf(2, "cd: failed to updated OLDPWD\n");
		return (0);
	}
	return (path);
}

t_string const	*set_pwd(char const *str)
{
	static t_string	*path = 0;
	t_string const	*ret;

	if (path == 0)
	{
		ZERO_IF_FAIL((path = string_create(32)));
	}
	if (!str)
		return (path);
	if (*path->buffer)
		ret = set_oldpwd(path->buffer);
	else
		ret = set_oldpwd(str);
	if (!ret)
		return (0);
	string_clear(path);
	if (!string_append(path, str))
		return (0);
	if (ft_setenv("PWD", path->buffer, 1) == -1)
	{
		ft_dprintf(2, "cd: failed to updated PWD\n");
		return (0);
	}
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
		string_delete_n(path, pos, 3);
		return (1);
	}
	path->buffer[pos] = tmp;
	string_delete_n(path, (begin + 1) - path->buffer,
			pos - (begin - path->buffer) + 2);
	string_replace(path, "//", "/");
	return (1);
}

int				clean_back_path(t_string *path)
{
	int		pos;

	while ((pos = string_find(path, "../")) >= 1)
	{
		if (path->buffer[pos - 1] != '/')
			return (0);
		if (!remove_previous_path(path, pos - 1))
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
	return (1);
}

t_string		*clean_path(char *path)
{
	t_string		*str;
	t_string const	*pwd;

	pwd = set_pwd(0);
	ZERO_IF_FAIL(str = string_create(ft_strlen(path) + pwd->size + 2));
	if (path[0] != '/')
		string_append(str, pwd->buffer);
	string_append(str, "/");
	string_append(str, path);
	string_replace(str, "//", "/");
	if (!clean_back_path(str))
	{
		ft_dprintf(2, "cd: no such file or directory: %s\n", path);
		return (0);
	}
	string_replace(str, "./", "");
	string_replace(str, "//", "/");
	if (str->size > 1 && str->buffer[str->size - 1] == '/')
		string_delete(str, str->size - 1);
	return (str);
}
