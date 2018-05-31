/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 19:07:49 by gfloure           #+#    #+#             */
/*   Updated: 2018/05/31 04:16:21 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <environment.h>
#include <localvar.h>
#include <execute.h>

int		unset_error(int mode, char *arg)
{
	if (mode == -1)
		ft_dprintf(2, "%s: Usage: unset [-f] [-v] [name..]\n", arg);
	else if (mode == -2)
	{
		ft_dprintf(2, "%s: unset: cannot simultaneously unset a", arg);
		ft_dprintf(2, " function and a variable\n");
	}
	else if (mode == -3)
		ft_dprintf(2, "%s: unset: not enough arguments\n", arg);
	return (-1);
}

void	localenv_remove_if(char const *data, t_predf predicate)
{
	array_remove_if(get_environment_array(), &data,
		(t_freef)&free_wrapper, predicate);
	array_remove_if(get_localvar_array(), &data,
		(t_freef)&free_wrapper, predicate);
}

int		localfunc_remove(char *name)
{
	ft_dprintf(2, "unset -f %s [...]\n", name);
	return (1);
}

int		check_opt(char **argv)
{
	int	i;
	int	y;
	int	opt;

	i = 0;
	opt = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		y = 0;
		if (!argv[i][1])
			return (-3);
		while (argv[i][++y])
		{
			if (argv[i][y] == 'v')
				opt = opt == 0 && opt != -1 ? 1 : -2;
			else if (argv[i][y] == 'f')
				opt = opt == 0 && opt != -1 ? 2 : -2;
			else
				opt = -1;
		}
	}
	return (opt);
}

int		builtin_unset(int argc, char **argv)
{
	int	i;
	int	opt;

	if ((opt = check_opt(argv)) < 0)
		return (unset_error(opt, argv[0]));
	if ((i = opt > 0 ? 2 : 1) >= argc)
		return (unset_error(-3, argv[0]));
	while (i < argc)
	{
		if (opt == 1)
			localenv_remove_if(argv[i], (t_predf) & glob_match_wrapper);
		if (opt == 2)
			localfunc_remove(argv[i]);
		else
			localenv_remove_if(argv[i], (t_predf) & glob_match_wrapper);
		if (glob_match(argv[i], "PATH"))
			generate_paths();
		i++;
	}
	return (0);
}
