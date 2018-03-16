/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:23:34 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/16 10:36:20 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <lexer.h>
#include <token.h>
#include <execute.h>

char		*token_get_string(t_token *token)
{
	char	*str;

	if (token->begin)
		str = ft_strndup(token->begin, token->size);
	else
		str = ft_strdup("");
	if (!str)
		return (0);
	remove_backslash(str);
	ZERO_IF_FAIL(str = expand(str));
	remove_quotes(str);
	return (str);
}

int			token_get_int(t_token *token)
{
	char	*str;
	int		nbr;

	ZERO_IF_FAIL(str = token_get_string(token));
	nbr = ft_atoi(str);
	free(str);
	return (nbr);
}

int			add_token(t_array *tokens, t_tag type, char const *begin,
															size_t size)
{
	t_token	token;

	fill_token(&token, type, begin, size);
	if (array_push_back(tokens, &token))
		return (1);
	return (0);
}

int			push_newline_token(t_array *tokens, char const *input, int start)
{
	t_token	token;

	fill_token(&token, NEWLINE, input + start, 1);
	if (!array_push_back(tokens, &token))
		return (-1);
	return (start + 1);
}

t_token		emit_token(t_tag type, char const *input, int start, int end)
{
	t_token	token;

	token.type = type;
	token.begin = input + start;
	token.size = end - start;
	return (token);
}

void		fill_token(t_token *token, t_tag type, char const *begin,
															size_t size)
{
	token->type = type;
	token->begin = begin;
	token->size = size;
}
