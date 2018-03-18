/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:56:11 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/18 16:49:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <lexer.h>
#include <token.h>

static int	lex_simple_redirection(t_array *tokens, char const *input,
																int start)
{
	if (input[start] == '<')
	{
		ZERO_IF_FAIL(add_token(tokens, LESS, input + start, 1));
	}
	else if (input[start] == '>')
	{
		ZERO_IF_FAIL(add_token(tokens, GREATER, input + start, 1));
	}
	else
		return (0);
	return (1);

}

static int	heredoc_token_size(char const *input, int start,
								char const *eof_begin, int eof_size)
{
	while (input[start])
	{
		if (input[start] == '\n')
		{
			if (ft_strnequ(input + start + 1, eof_begin, eof_size))
				return (start + 1);
		}
		++start;
	}
	return (0);
}

static int	lex_heredoc(t_array *tokens, char const *input, int start)
{
	char const	*eof_token_begin;
	int			eof_token_size;
	int			pos;

	while (input[start] && ft_is_whitespace(input[start]))
		++start;
	eof_token_begin = input + start;
	eof_token_size = 0;
	while (input[start] && input[start] != '\n')
	{
		++eof_token_size;
		++start;
	}
	if (input[start])
		++start;
	ZERO_IF_FAIL(pos = heredoc_token_size(input, start,
						eof_token_begin, eof_token_size));
	ZERO_IF_FAIL(add_token(tokens, TOKEN, input + start, start - pos));
	return (pos + eof_token_size + 1);
}

int			lex_redirection(t_array *tokens, char const *input, int start)
{
	if (input[start] == '<' && input[start + 1] == '<')
	{
		ZERO_IF_FAIL(add_token(tokens, DLESS, input + start, 2));
		return (lex_heredoc(tokens, input, start + 2));
	}
	else if (input[start] == '<' && input[start + 1] == '&')
	{
		ZERO_IF_FAIL(add_token(tokens, LESSAND, input + start, 2));
	}
	else if (input[start] == '>' && input[start + 1] == '>')
	{
		ZERO_IF_FAIL(add_token(tokens, DGREATER, input + start, 2));
	}
	else if (input[start] == '>' && input[start + 1] == '&')
	{
		ZERO_IF_FAIL(add_token(tokens, GREATERAND, input + start, 2));
	}
	else
		return (lex_simple_redirection(tokens, input, start));
	return (2);
}
