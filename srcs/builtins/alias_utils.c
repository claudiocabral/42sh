/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:57:19 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/12 04:09:26 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>

int				get_next(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			return (i + 1);
		i++;
	}
	return (i);
}

int				ft_strchral(char *s)
{
	int			i;

	i = -1;
	while (s[++i])
		if (s[i] == ' ' || s[i] == ';')
			return (i);
	return (i >= 1 ? i : -1);
}

int				loop_alias_replace(char **tmp, char **tmp2, char **tmp1)
{
	char		*tmp3;
	char		*tmp4;
	int			i;

	i = 0;
	while (1)
	{
		*tmp1 = ft_strsub(*tmp2, ft_strchri(*tmp2, '=') + 1, ft_strlen(*tmp2));
		*tmp1 = ft_strjoinfree("alias ", *tmp1, 'R');
		*tmp2 = ft_getalias(*tmp1);
		if (*tmp2)
			tmp4 = ft_strjoin("alias ", *tmp2);
		tmp3 = tmp4 && *tmp2 ? ft_getalias(tmp4) : 0;
		if (!(*tmp2) || (tmp3 && (ft_strcmp(&(*tmp1)[6], tmp3) == 0)))
		{
			tmp4 && *tmp2 ? free(tmp4) : 0;
			return (0);
		}
		*tmp = *tmp2 ? *tmp2 : *tmp;
		*tmp1 ? free(*tmp1) : 0;
		tmp4 ? free(tmp4) : 0;
		i++;
		if (i > 100)
			return (i);
	}
}

int				get_alias_to_replace(t_string *str, int *i)
{
	char		*tmp;
	char		*tmp1;
	int			ret;

	while ((ret = ft_strchral(&str->buffer[*i])) != -1)
	{
		tmp = ft_strsub(str->buffer, *i, ret);
		tmp1 = alias_replace_process(tmp);
		string_delete_n(str, *i, ret);
		string_insert_string(str, tmp1, *i);
		tmp ? free(tmp) : 0;
		*i += get_next(&str->buffer[*i]);
	}
	return (1);
}

int				is_valid_alias(char *alias)
{
	int		i;

	i = ft_strchri(alias, '=');
	if (i == 0)
		return (-1);
	i = 0;
	while (alias[i])
		if (!good_char(alias[i++]))
			return (-1);
	return (1);
}
