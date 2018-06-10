/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:09:22 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/10 15:02:08 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <builtins.h>

int			ft_strcmp_untilb(char const *s1, char const *s2, char c)
{
	while (1)
	{
		if (*s2 == c && *s1 == '\0')
			return (0);
		if (*s1 == '\0' || *s1 != *s2)
			break ;
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int			ft_strncmp_wrapperb(char const **a, char const **b)
{
	return (ft_strcmp_untilb(*a, *b, '='));
}

int			identify_opt(char **av, t_array *env, int mode)
{
	int		i;
	int		j;
	int		opt;

	i = 0;
	opt = -1;
	while (av[++i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--"))
			continue ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j++] != 'p')
			{
				mode == 1 ? export_error(av[i], env, 1) :
					alias_error(av[i], av[i][j - 1], 1);
				return (-1);
			}
			opt++;
		}
	}
	if (opt >= 0 && mode == 2)
		array_apply(env, 0, (t_applyf) & print_alias_all);
	return (i > 1 ? i : 1);
}
