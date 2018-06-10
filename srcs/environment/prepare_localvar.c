/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_localvar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:59:40 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/10 14:14:16 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <localvar.h>
#include <builtins.h>
#include <environment.h>

static t_array *g_localvar = 0;

int			ft_prepare_localvar(void)
{
	ZERO_IF_FAIL(g_localvar = array_create(sizeof(char *), 32));
	return (1);
}

t_array		*get_localvar_array(void)
{
	return (g_localvar);
}

char		*ft_getvar(char const *var)
{
	char	**ptr;
	char	*val;

	val = 0;
	ptr = array_find(g_localvar, &var, (t_cmpf) & ft_strncmp_wrapperb);
	if (ptr)
	{
		val = ft_strchr(*ptr, '=');
		val = val ? val + 1 : 0;
	}
	return (val);
}

char		*ft_getenv_b(char const *var)
{
	char	**ptr;
	char	*val;

	val = 0;
	ptr = array_find(get_environment_array(), &var,
			(t_cmpf) & ft_strncmp_wrapperb);
	if (ptr)
	{
		val = ft_strchr(*ptr, '=');
		val = val ? val + 1 : 0;
	}
	return (val);
}
