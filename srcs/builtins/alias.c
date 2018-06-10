/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:50:09 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/10 17:15:13 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <array.h>
#include <ft_printf.h>
#include <libft.h>
#include <stdlib.h>
#include <localvar.h>
#include <ft_string.h>

int				alias_error(char *av, char opt, int mode)
{
	if (mode == 1)
	{
		ft_dprintf(2, "42sh: alias: -%c: invalid option\n", opt);
		ft_dprintf(2, "usage: alias [-p] [name..]\n");
	}
	else if (mode == 2)
		ft_dprintf(2, "42sh: alias: %s: not found\n", av);
	else if (mode == 3)
		ft_dprintf(2, "42sh: %s: alias not found\n", av);
	return (-1);
}

char			*alias_replace_process(char *av)
{
	char		*tmp;
	char		*tmp1;
	char		*tmp2;
	int			i;
	t_string	*str;

	str = string_create(0);
	string_append(str, "alias ");
	string_append(str, av);
	tmp = ft_getalias(str->buffer);
	tmp1 = NULL;
	if (tmp)
	{
		tmp2 = tmp;
		i = loop_alias_replace(&tmp, &tmp2, &tmp1);
		string_free(str);
		i < 100 && tmp1 ? free(tmp1) : 0;
		return (tmp && i < 100 ? tmp : av);
	}
	string_free(str);
	return (tmp ? tmp : av);
}

char			*alias_replace(char *input)
{
	t_string	*str;
	char		*tmp;
	int			i;

	i = 0;
	str = string_create(0);
	tmp = ft_strdup(input);
	input ? free(input) : 0;
	string_append(str, tmp);
	get_alias_to_replace(str, &i);
	input = ft_strdup(str->buffer);
	tmp ? free(tmp) : 0;
	string_free(str);
	return (input);
}

int				core_alias(char *av)
{
	char		*tmp;
	char		**var;
	int			ret;

	ZERO_IF_FAIL(tmp = ft_strjoinfree("alias ",
				ft_strsub(av, 0, ret = ft_strchri(av, '=')), 'R'));
	if (is_valid_alias(av) == -1)
	{
		tmp ? free(tmp) : 0;
		return (alias_error(av, 0, 2));
	}
	var = array_find(get_alias_array(), &tmp, (t_cmpf) & ft_strncmp_wrapperb);
	remove_quotes_var(&av[ret + 1]);
	tmp ? free(tmp) : 0;
	if (var)
	{
		free(*var);
		*var = ft_strjoin("alias ", av);
	}
	else
	{
		tmp = ft_strjoin("alias ", av);
		array_push_back(get_alias_array(), &tmp);
	}
	return (1);
}

int				builtin_alias(int argc, char **av)
{
	t_array		*alias;
	int			i;
	int			ret;

	if (!(alias = get_alias_array()))
		return (-1);
	if ((i = identify_opt(av, alias, 2)) < 0)
		return (-1);
	if (argc == 1)
		return (print_alias(NULL, alias, 0));
	while (av[i])
	{
		if ((ret = ft_strchri(av[i], '=')) != -1)
			core_alias(av[i]);
		else
			return (print_alias(av, alias, i));
		i++;
	}
	return (1);
}
