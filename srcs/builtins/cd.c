/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:01:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/04 04:21:57 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <ft_printf.h>
#include <ft_string.h>
#include <environment.h>
#include <builtins.h>

int			cd_error(char *av, char opt, int mode)
{
	if (mode == 1)
		ft_dprintf(2, "42sh: cd: OLDPWD not set\n");
	else if (mode == 2)
	{
		ft_dprintf(2, "42sh: cd: Too many arguments\n");
		return (1);
	}
	else if (mode == 3)
	{
		ft_dprintf(2, "42sh: cd: usage: cd [-L|-P] [dir]\n");
		return (1);
	}
	else if (mode == 4)
		ft_dprintf(2, "42sh: cd: -%c: invalid option\n", opt);
	else if (mode == 5)
	{
		ft_dprintf(2, "42sh: cd: failed to change to directory: %s\n", av);
		return (1);
	}
	return (-1);
}

int			parse_args(int *argc, char ***argv)
{
	int	flag;

	flag = 0;
	while (--(*argc) && (*(++(*argv)))[0] == '-')
	{
		if (ft_strequ(**argv, "--"))
		{
			*argc -= 1;
			*argv += 1;
			break ;
		}
		if (ft_strequ(**argv, "-"))
			break ;
		while (*(++(**(argv))))
		{
			if (***argv == 'P')
				flag = 1;
			else if (***argv == 'L')
				flag = 0;
			else
				return (cd_error(NULL, ***argv, 4));
		}
	}
	return (flag);
}

int			cd_chdir(char const *path)
{
	if (!path)
		return (1);
	if (ft_strequ(path, ""))
		return (0);
	if (chdir(path) != -1)
		set_pwd(path);
	else
		return (cd_error((char *)path, 0, 5));
	return (0);
}

int			cd_flag(char *path)
{
	int			ret;
	char		*new_path;
	char		*cur;

	cur = ft_strdup(ft_getenv_safe("PWD"));
	ret = chdir(path);
	new_path = NULL;
	if (ret != -1)
	{
		ft_setenv("OLDPWD", cur, 1);
		new_path = getcwd(0, 0);
		ft_setenv("PWD", new_path, 1);
		set_pwd(new_path);
		free(new_path);
	}
	else
		cd_error(path, 0, 5);
	cur ? free(cur) : 0;
	return (ret);
}

int			cd(int argc, char **argv)
{
	t_string	*path;
	char		*path_ptr;
	int			flag;

	path_ptr = NULL;
	if ((flag = parse_args(&argc, &argv)) == -1)
		return (cd_error(NULL, 0, 3));
	if (argc == 0)
		path_ptr = ft_getenv_safe("HOME");
	else if (argc == 1)
	{
		if (!(path_ptr = ft_strequ(*argv, "-") ? ft_getenv("OLDPWD") : *argv))
			return (cd_error(NULL, 0, 1));
	}
	else
		return (cd_error(NULL, 0, 2));
	if (!(path = clean_path(path_ptr)))
		return (1);
	if (flag == 1)
		flag = cd_flag(path->buffer);
	else
		flag = cd_chdir(path->buffer);
	string_free(path);
	return (flag);
}
