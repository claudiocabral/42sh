/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:39:10 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/13 02:04:15 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <token.h>
#include <execute.h>
#include <localvar.h>

int			skip_until_equals(char *token, int pos, int target)
{
	while (token[pos] && (token[pos] != token[target]))
	{
		if (token[pos] == '\\')
			++pos;
		if (token[pos] != target)
			++pos;
		else
			return (pos);
	}
	return (pos);
}

void		remove_all_quotes(char *token)
{
	int		i;
	int		y;

	i = 0;
	while (token[i])
	{
		if (token[i] && token[i] == '\\')
			i += 2;
		if ((size_t)i > ft_strlen(token) || !token[i])
			break ;
		if (token[i] && token_quote(token[i]))
		{
			y = i + 1;
			y = skip_until_equals(token, y, i);
			if (token[y] == token[i])
			{
				remove_quotes(&token[y]);
				remove_quotes(&token[i]);
				i = y - 2;
			}
		}
		i++;
	}
}

char		*token_get_string(t_token *token, int only_var)
{
	char	*str;

	if (token->begin)
		str = ft_strndup(token->begin, token->size);
	else
		str = ft_strdup("");
	if (!str)
		return (0);
	ZERO_IF_FAIL(str = expand(str));
	ZERO_IF_FAIL(str = expand_localvar(str));
	change_special_char(str);
	remove_all_quotes(str);
	remove_backslash(str);
	set_localvar(str, only_var);
	return (str);
}

int			token_get_int(t_token *token)
{
	char	*str;
	int		nbr;

	ZERO_IF_FAIL(str = token_get_string(token, 0));
	nbr = ft_atoi(str);
	free(str);
	return (nbr);
}
