/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:01:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/07 14:33:26 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <ft_printf.h>
#include <ft_string.h>
#include <environment.h>
#include <builtins.h>

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
		while (*(++(**(argv))))
		{
			if (***argv == 'P')
				flag = 1;
			else if (***argv == 'L')
				flag = 0;
			else
			{
				ft_dprintf(2, "cd: -%c: invalid option\n", ***argv);
				return (-1);
			}
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
	{
		ft_dprintf(2, "cd: failed to change to directory: %s\n", path);
		return (1);
	}
	return (0);
}

int			cd_flag(char *path)
{
	int			ret;
	char		*new_path;

	ret = chdir(path);
	if (ret != -1)
	{
		new_path = getcwd(0, 0);
		ft_setenv("OLDPWD", ft_getenv_safe("PWD"), 1);
		ft_setenv("PWD", new_path, 1);
		set_pwd(new_path);
		free(new_path);
	}
	else
		ft_dprintf(2, "cd: failed to change to directory: %s\n", path);
	return (ret);
}

static int	cd_usage(void)
{
	ft_dprintf(2, "cd: usage: cd [-L|-P] [dir]\n");
	return (1);
}

int			cd(int argc, char **argv)
{
	t_string	*path;
	char		*path_ptr;
	int			flag;

	if ((flag = parse_args(&argc, &argv)) == -1)
		return (cd_usage());
	if (argc == 0)
		path_ptr = ft_getenv_safe("HOME");
	else if (argc == 1)
		path_ptr = ft_strequ(*argv, "-") ? ft_getenv_safe("OLDPWD") : *argv;
	else
	{
		ft_dprintf(2, "cd: too many arguments\n");
		return (1);
	}
	if (!(path = clean_path(path_ptr)))
		return (1);
	if (flag == 1)
		flag = cd_flag(path->buffer);
	else
		flag = cd_chdir(path->buffer);
	string_free(path);
	return (flag);
}
