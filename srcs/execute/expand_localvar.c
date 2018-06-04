/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_localvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:13:20 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/04 03:30:02 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <localvar.h>
#include <environment.h>
#include <execute.h>

char	*search_allvar(char *value)
{
	char	*str;

	if (!(str = ft_getenv(value)))
		if (!(str = ft_getvar(value)))
			str = NULL;
	return (str ? ft_strdup(str) : NULL);
}

int		remove_quotes_var(char *s)
{
	if ((s[0] == '"' && s[ft_strlen(s) - 1] == '"')
			|| (s[0] == '\'' && s[ft_strlen(s) - 1] == '\''))
	{
		remove_quotes(&s[0]);
		remove_quotes(&s[ft_strlen(s) - 1]);
	}
	return (1);
}

void	replace_var(t_string *str, int *i)
{
	char		*tmp;
	char		*tmp1;
	int			j;

	j = 1;
	while (str->buffer[*i + j] && ft_is_whitespace(str->buffer[*i + j]) == 0)
		if (str->buffer[*i + ++j] == '$')
			break ;
	if (j > 1)
	{
		tmp = ft_strsub(str->buffer, *i, j);
		tmp1 = ft_strcmp(tmp + 1, "$") == 0 ? ft_itoa((int)getpid()) :
			search_allvar(tmp + 1);
		tmp1 = !tmp1 ? "" : tmp1;
		*i -= 1;
		string_replace(str, tmp, tmp1);
		tmp ? free(tmp) : 0;
		ft_strlen(tmp1) > 1 ? free(tmp1) : 0;
	}
}

char	*expand_localvar(char *value)
{
	t_string	*str;
	int		i;

	i = -1;
	str = string_create(0);
	str = string_append(str, value);
	while (str->buffer[++i])
	{
		if (str->buffer[i] == '$' && (str->buffer[i > 0 ? i - 1 : 0] != '\\'))
			replace_var(str, &i);
		else if (str->buffer[i] == '$' &&
				(str->buffer[i > 0 ? i - 1 : 0] == '\\'))
			string_delete(str, i - 1);
	}
	value ? free(value) : 0;
	value = ft_strdup(str->buffer);
	str ? string_free(str) : 0;
	return (value);
}
