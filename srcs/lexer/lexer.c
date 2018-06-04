/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:41:32 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/02 04:24:53 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shellma.h>
#include <array.h>
#include <token.h>
#include <ft_printf.h>

int			lex_quote(t_array *tokens, t_slice input)
{
	int	pos;

	pos = input.size + 1;
	while (input.ptr[pos] && input.ptr[pos] != input.ptr[input.size])
		++pos;
	if (input.ptr[pos] != input.ptr[input.size])
		return (-1);
	if (add_token(tokens, TOKEN, input.ptr + input.size, pos - input.size))
		return (pos + 1);
	return (-1);
}

int			lex_semicolon(t_array *tokens, t_slice input)
{
	if (input.ptr[input.size + 1] != ';')
		return (add_token(tokens, SEMICOLON, input.ptr + input.size, 1));
	return (add_token(tokens, DSEMI, input.ptr + input.size, 2));
}

int			lex_operator(t_array *tokens, t_slice input, char const **heredoc)
{
	int	ret;

	ret = 0;
	if (get_quote(-42) == 0)
	{
		if (input.ptr[input.size] == ';')
			ret = lex_semicolon(tokens, input);
		else if (input.ptr[input.size] == '&')
		{
			if (input.ptr[input.size + 1] == '&')
				ret = add_token(tokens, AND_IF, input.ptr + input.size, 2);
			else
				ret = add_token(tokens, AND, input.ptr + input.size, 1);
		}
		else if (input.ptr[input.size] == '|')
		{
			if (input.ptr[input.size + 1] == '|')
				ret = add_token(tokens, OR_IF, input.ptr + input.size, 2);
			else
				ret = add_token(tokens, PIPE, input.ptr + input.size, 1);
		}
		else if (input.ptr[input.size] == '<' || input.ptr[input.size] == '>')
			ret = lex_redirection(tokens, input, heredoc);
		if (ret)
			return (input.size + ret);
	}
	return (-1);
}

int			lex_token(t_array *tokens, t_slice input, int pos)
{
	while (input.ptr[pos])
	{
		if (input.ptr[pos] == '\\')
		{
			++pos;
			if (!input.ptr[pos])
				break ;
		}
		else if (token_delimiter(input.ptr[pos]))
			break ;
		++pos;
	}
	if (add_token(tokens, TOKEN, input.ptr + input.size, pos - input.size))
		return (pos);
	return (-1);
}

int			lex_digit(t_array *tokens, t_slice input)
{
	int		pos;

	pos = input.size;
	while (ft_isdigit(input.ptr[pos]))
		++pos;
	if (input.ptr[pos] == '<' || input.ptr[pos] == '>')
	{
		if (add_token(tokens, IO_NUMBER, input.ptr + input.size,
					pos - input.size))
			return (pos);
		return (-1);
	}
	return (lex_token(tokens, input, pos));
}

int			lex_text(t_array *tokens, t_slice input, char const **heredoc)
{
	char const	*end;

	end = *heredoc;
	if (*end)
		--end;
	while (input.size >= 0 && (input.ptr + input.size < end)
							&& input.ptr[input.size])
	{
		if (ft_is_whitespace(input.ptr[input.size]))
			++input.size;
		else if (token_newline(input.ptr[input.size]))
			input.size = push_newline_token(tokens, input.ptr, input.size);
		else if (token_operator(input.ptr[input.size]))
			input.size = lex_operator(tokens, input, heredoc);
		else if (ft_isdigit(input.ptr[input.size]))
			input.size = lex_digit(tokens, input);
		else if (token_quote(input.ptr[input.size]))
			input.size = lex_quote(tokens, input);
		else if (token_comment(input.ptr[input.size]))
			input.size = lex_comment(input);
		else
			input.size = lex_token(tokens, input, input.size);
	}
	return (input.size == -1 ? -1 : 1);
}
