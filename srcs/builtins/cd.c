/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:01:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/03 10:09:13 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <ft_printf.h>
#include <ft_string.h>
#include <environment.h>
#include <builtins.h>

int	parse_args(int *argc, char ***argv)
{
	int	flag;

	*argc = *argc - 1;
	*argv = *argv + 1;
	if (*argc == 0 || ((*argv)[0][0] != '-') || (*argv)[0][1] == 0)
		return (0);
	if ((*argv)[0][1] == 'L')
		flag = 1;
	else if ((*argv)[0][1] == 'P')
		flag = -1;
	else
		return (0);
	if ((*argv)[0][2] == 'L')
		flag = 1;
	else if ((*argv)[0][2] == 'P')
		flag = -1;
	else if ((*argv)[0][2] == 0)
	{
		*argc = *argc - 1;
		*argv = *argv + 1;
		return (flag);
	}
	return (0);
}

int	cd_chdir(char const *path)
{
	int			ret;

	if (!path)
		return (1);
	if ((ret = chdir(path)) == 0)
	{
		if ((ret = ft_setenv("OLDPWD", ft_getenv("PWD"), 1)) != 0)
			ft_dprintf(2, "cd: failed to updated OLDPWD\n");
		if ((ret = ft_setenv("PWD", path, 1)) != 0)
			ft_dprintf(2, "cd: failed to updated PWD\n");
	}
	else
		ft_dprintf(2, "cd: failed to change directory\n");
	return (ret != 0);
}

void	cd_canonical(char *path, char buff[MAXPATHLEN])
{
	(void)path;
	(void)buff;
}

int		cd_noflag(char *path)
{
	int			ret;
	char		*new_path;

	ret = chdir(path);
	if (ret != -1)
	{
		new_path = getcwd(0, 0);
		ft_setenv("OLDPWD", ft_getenv("PWD"), 1);
		ft_setenv("PWD", new_path, 1);
		free(new_path);
	}
	else
		ft_dprintf(2, "cd: failed to change to directory: %s\n", path);
	return (ret);
}

int cd_L(char *path)
{
	(void)path;
	return (1);
}

int cd_P(char *path)
{
	(void)path;
	return (1);
}

int	cd(int argc, char **argv)
{
	char	*path;
	int		flag;

	flag = parse_args(&argc, &argv);
	if (argc == 0)
	{
		return (cd_chdir(ft_getenv("HOME")));
	}
	else if (argc == 1)
	{
		if (!(path = ft_strequ(*argv, "-") ? ft_getenv("OLDPWD") : *argv))
		{
			ft_dprintf(2, "cd: OLDPWD not set\n");
			return (1);
		}
		if (flag == 1)
			return (cd_L(path));
		else if (flag == -1)
			return (cd_P(path));
		return (cd_noflag(path));
	}
	ft_dprintf(2, "cd: too many arguments\n");
	return (1);
}
