/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:04:46 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/08 18:07:25 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <environment.h>
#include <localvar.h>
#include <execute.h>

int		unset_error(int mode)
{
	if (mode == -1)
		ft_dprintf(2, "42sh: Usage: unset [-v] [name..]\n");
	else if (mode == -3)
		ft_dprintf(2, "42sh: unset: not enough arguments\n");
	return (-1);
}

void	localenv_remove_if(char const *data, t_predf predicate)
{
	array_remove_if(get_environment_array(), &data,
		(t_freef) & free_wrapper, predicate);
	array_remove_if(get_localvar_array(), &data,
		(t_freef) & free_wrapper, predicate);
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
		if (ft_strequ(argv[i], "--"))
			continue ;
		y = 0;
		if (!argv[i][1])
			return (-3);
		while (argv[i][++y])
		{
			if (argv[i][y] == 'v')
				opt = opt == 0 && opt != -1 ? 1 : -2;
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
		return (unset_error(opt));
	if ((i = opt > 0 ? 2 : 1) >= argc)
		return (unset_error(-3));
	while (i < argc)
	{
		if (opt == 1 || opt == 0)
			localenv_remove_if(argv[i], (t_predf)&glob_match_wrapper);
		if (glob_match(argv[i], "PATH"))
			generate_paths();
		i++;
	}
	return (0);
}
