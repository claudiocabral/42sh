/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:01:28 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/08 18:01:52 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>
#include <ft_printf.h>

void			print_alias_all(char const **alias, void *dummy)
{
	t_string	*tmp;
	int			ret;
	const char	*str;

	(void)dummy;
	ret = 0;
	str = *alias;
	if (str)
	{
		tmp = string_create(36);
		string_append(tmp, str);
		ret = ft_strchri(tmp->buffer, '=');
		if (tmp->buffer[ret + 1])
		{
			string_insert(tmp, '\'', ret + 1);
			string_insert(tmp, '\'', ft_strlen(tmp->buffer));
		}
		ft_printf("%s", tmp->buffer);
		!tmp->buffer[ret + 1] ? ft_printf("\'\'\n") : ft_printf("\n");
		tmp ? string_free(tmp) : 0;
	}
}

int				print_alias(char **av, t_array *alias, int i)
{
	const char	**str;
	char		*tmp;
	t_array		*array;

	if ((av && !av[i]) || !av)
	{
		if (alias)
			array_apply(alias, 0, (t_applyf) & print_alias_all);
		return (1);
	}
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	while (av && av[i])
	{
		tmp = ft_strjoin("alias ", av[i]);
		if ((str = array_find(alias, &tmp, (t_cmpf) & ft_strncmp_wrapperb)))
			array_push_back(array, str);
		else
			alias_error(av[i], 0, 3);
		tmp ? free(tmp) : 0;
		str = NULL;
		i++;
	}
	array_apply(array, 0, (t_applyf) & print_alias_all);
	array_free(array, &noop);
	return (1);
}
