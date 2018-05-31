/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 05:36:28 by gfloure           #+#    #+#             */
/*   Updated: 2018/05/31 04:04:19 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <localvar.h>
#include <stdlib.h>
#include <builtins.h>
#include <environment.h>

int				token_var_valid(int save)
{
	static int	bu;

	if (save != -1)
		bu = save;
	return (bu);
}

int				is_valid_var(char *av)
{
	int			i;

	i = 0;
	if (av[i] && (ft_isalpha(av[i]) || av[i] == '_'))
		while (av[++i] && av[i] != '=')
			if ((!ft_isalnum(av[i])) && (!(av[i] == '_')))
				return (-1);
	return (i > 0 ? 1 : -1);
}

char			**get_elem(char *elem)
{
	char		**var;

	var = array_find(get_environment_array(), &elem, (t_cmpf) &
			ft_strncmp_wrapperb);
	if (var)
		return (var);
	var = array_find(get_localvar_array(), &elem, (t_cmpf) &
			ft_strncmp_wrapperb);
	return (var);
}

int			export_localvar(char *var)
{
	char		*tmp;
	char		*tmp1;
	char		**var_elem;

	ZERO_IF_FAIL(tmp = ft_strsub(var, 0, ft_strchri(var, '=')));
	if (is_valid_var(var) == -1)
		return (-1);
	if ((var_elem = get_elem(tmp)))
	{
		free(*var_elem);
		*var_elem = ft_strdup(var);
	}
	else
	{
		tmp1 = ft_strdup(var);
		array_push_back(get_localvar_array(), &tmp1);
	}
	tmp ? free(tmp) : 0;
	return (1);
}

void			set_localvar(char *token, int only_var)
{
	int			ret;
	int			before_anycmd;

	before_anycmd = token_var_valid(-1);
	if (((ret = ft_strchri(token, '=')) != -1) && before_anycmd == 0)
	{
		if (only_var)
			if (export_localvar(token) == -1)
				return ;
		ft_bzero(token, ft_strlen(token));
	}
	else
		token_var_valid(-2);
}
