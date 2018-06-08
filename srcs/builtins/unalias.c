/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:07:41 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/08 18:09:09 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <ft_printf.h>
#include <array.h>
#include <execute.h>
#include <environment.h>
#include <localvar.h>

int			unalias_error(char *av, char opt, int mode)
{
	if (mode == 1)
	{
		ft_dprintf(2, "42sh: unalias: -%c: invalid option\n", opt);
		ft_dprintf(2, "unalias: usage: unalias [-a] [name...]");
	}
	else if (mode == 2)
		ft_dprintf(2, "42sh: unalias: %s: not found\n", av);
	else if (mode == 3)
		ft_dprintf(2, "42sh: unalias: not enough arguments\n");
	return (-1);
}

int			id_opt(char **av, t_array *alias)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (av[++i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--"))
			continue ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j++] != 'a')
				return (unalias_error(av[i], av[i][j - 1], 1));
			else
				array_clear(alias, (t_freef) & free_wrapper);
		}
	}
	return (i > 1 ? i : 1);
}

int			alias_remove_if(char const *data, t_predf predicate)
{
	char	*tmp;
	int		size;

	size = array_size(get_alias_array());
	tmp = ft_strjoin("alias ", data);
	array_remove_if(get_alias_array(), &tmp, (t_freef) & free_wrapper,
		predicate);
	if (size == array_size(get_alias_array()))
		unalias_error((char *)data, 0, 2);
	tmp ? free(tmp) : 0;
	return (1);
}

int			builtin_unalias(int argc, char **argv)
{
	t_array	*alias;
	int		i;

	if (argc == 1)
		return (unalias_error(NULL, 0, 3));
	if (!(alias = get_alias_array()))
		return (-1);
	if ((i = id_opt(argv, alias)) < 0)
		return (-1);
	while (argv[i])
		alias_remove_if(argv[i++], (t_predf)&glob_match_wrapper);
	return (1);
}
