/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 06:05:15 by gfloure           #+#    #+#             */
/*   Updated: 2018/05/25 16:47:41 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <builtins.h>
#include <stdio.h>

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

int			identify_opt(char **av, t_array *env)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	if (av[i])
	{
		while (av[i] && av[i][0] == '-')
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][j++] != 'p')
				{
					export_error(av[i], env, 1);
					return (-1);
				}
			}
			i++;
		}
	}
	return (j > 1 ? i : 0);
}
