/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_localvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:13:20 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/10 16:33:45 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <localvar.h>
#include <environment.h>
#include <execute.h>

char		*search_allvar(char *value)
{
	char	*str;

	if (!(str = ft_getenv(value)))
		if (!(str = ft_getvar(value)))
			str = NULL;
	return (str ? str : "");
}

int			remove_quotes_var(char *s)
{
	if ((s[0] == '"' && s[ft_strlen(s) - 1] == '"')
			|| (s[0] == '\'' && s[ft_strlen(s) - 1] == '\''))
	{
		remove_quotes(&s[0]);
		remove_quotes(&s[ft_strlen(s) - 1]);
	}
	return (1);
}

void		replace_var(t_string *str, int *i)
{
	char		*tmp;
	char		*tmp1;
	int			j;

	j = 1;
	while (str->buffer[*i + j] && ft_is_whitespace(str->buffer[*i + j]) == 0)
		if ((str->buffer[*i + ++j] == '$') || !ft_isalnum(str->buffer[*i + j]))
			break ;
	if (j > 1)
	{
		tmp = ft_strsub(str->buffer, *i, j);
		tmp1 = ft_strcmp(tmp + 1, "$") == 0 ? ft_itoa((int)getpid()) :
			ft_strdup(search_allvar(tmp + 1));
		tmp1 = !tmp1 ? ft_strdup("") : tmp1;
		string_delete_n(str, *i, j);
		string_insert_string(str, tmp1, *i);
		tmp ? free(tmp) : 0;
		*i += ft_strlen(tmp1) - 1;
		tmp1 ? free(tmp1) : 0;
	}
}

static char	*finish_expansion(char *value, t_string *str)
{
	free(value);
	if (str && str->buffer)
	{
		value = ft_strdup(str->buffer);
		string_free(str);
	}
	return (value);
}

char		*expand_localvar(char *value)
{
	t_string	*str;
	int			i;
	char		quote;

	i = -1;
	str = string_create(36);
	str = string_append(str, value);
	quote = 0;
	while (str->buffer[++i])
	{
		if (token_quote(str->buffer[i]))
		{
			if (quote == 0)
				quote = str->buffer[i];
			else
				quote = quote == str->buffer[i] ? 0 : quote;
		}
		if (str->buffer[i] == '\\')
			i += 2;
		if (!str->buffer[i])
			break ;
		if (str->buffer[i] == '$' && (quote != '\''))
			replace_var(str, &i);
	}
	return (finish_expansion(value, str));
}
