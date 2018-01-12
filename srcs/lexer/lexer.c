/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:41:32 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 14:04:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shellma.h>
#include <array.h>
#include <token.h>
#include <ft_printf.h>

int			lex_quote(t_array *tokens, char const *input, int start)
{
	int	pos;

	pos = start + 1;
	while (input[pos] && input[pos] != input[start])
		++pos;
	if (input[pos] != input[start])
		return (-1);
	if (add_token(tokens, TOKEN, input + start + 1, pos - start - 1))
		return (pos + 1);
	return (-1);
}

int			lex_operator(t_array *tokens, char const *input, int start)
{
	int	ret;

	ret = 0;
	if (input[start] == ';')
		ret = add_token(tokens, SEMICOLON, input + start, 1);
	else if (input[start] == '&')
		ret = add_token(tokens, AND, input + start, 1);
	else if (input[start] == '|')
		ret = add_token(tokens, PIPE, input + start, 1);
	if (ret)
		return (start + 1);
	return (-1);
}

int			lex_token(t_array *tokens, char const *input, int start, int pos)
{
	while (input[pos])
	{
		if (input[pos] == '\\')
		{
			++pos;
			if (!input[pos])
				break ;
		}
		else if (token_delimiter(input[pos]))
			break ;
		++pos;
	}
	if (add_token(tokens, TOKEN, input + start, pos - start))
		return (pos);
	return (-1);
}

int			lex_digit(t_array *tokens, char const *input, int start)
{
	int		pos;

	pos = start;
	while (ft_isdigit(input[pos]))
		++pos;
	if (input[pos] == '<' || input[pos] == '>')
	{
		if (add_token(tokens, IO_NUMBER, input + start, pos - start))
			return (pos);
		return (-1);
	}
	return (lex_token(tokens, input, start, pos));
}

int			lex_text(t_array *tokens, char const *input, int start)
{
	while (input[start])
	{
		while (ft_is_whitespace(input[start]))
			++start;
		if (!input[start])
			break ;
		if (token_newline(input[start]))
			start = push_newline_token(tokens, input, start);
		else if (token_operator(input[start]))
			start = lex_operator(tokens, input, start);
		else if (ft_isdigit(input[start]))
			start = lex_digit(tokens, input, start);
		else if (token_quote(input[start]))
			start = lex_quote(tokens, input, start);
		else
			start = lex_token(tokens, input, start, start);
		if (start == -1)
			return (-1);
	}
	return (1);
}
