/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:56:11 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/11 01:59:37 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <lexer.h>
#include <token.h>
#include <ft_printf.h>
#include <localvar.h>

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

static int	heredoc_token_size(char const **heredoc,
								char const *eof_begin, int eof_size)
{
	int	pos;

	pos = 0;
	while ((*heredoc)[pos])
	{
		if ((*heredoc)[pos] == '\n')
		{
			if (ft_strnequ((*heredoc) + pos + 1, eof_begin, eof_size))
				return (pos + 1);
		}
		++pos;
	}
	return (0);
}

char	*heredoc_token_var(char *s)
{
	char		*tmp;
	t_string	*str;
	int			i;

	i = ft_strlen(s) - 1;
	str = string_create(0);
	string_append(str, s);
	while (str->buffer[i] && str->buffer[i] != '\n')
		i--;
	if (!(tmp = ft_strsub(s, 0, i)) && (size_t)i < ft_strlen(s))
		return (NULL);
	if (!(tmp = expand_localvar(tmp)))
		return (NULL);
	string_delete_n(str, 0, i);
	string_insert_string(str, tmp, 0);
	free(tmp);
	tmp = ft_strdup(str->buffer);
	string_free(str);
	free(s);
	return (tmp);
}

static int	lex_heredoc(t_array *tokens, t_slice input, char const **heredoc)
{
	char const	*eof_token_begin;
	int			eof_token_size;
	int			pos;
	int			initial_size;

	initial_size = input.size;
	while (input.ptr[input.size] && ft_is_whitespace(input.ptr[input.size]))
		++input.size;
	eof_token_begin = input.ptr + input.size;
	eof_token_size = 0;
	while (input.ptr[input.size] && !ft_is_whitespace(input.ptr[input.size])
			&& input.ptr[input.size] != '\n')
	{
		++eof_token_size;
		++input.size;
	}
	ZERO_IF_FAIL(pos = heredoc_token_size(heredoc,
						eof_token_begin, eof_token_size));
	ZERO_IF_FAIL(add_token(tokens, TOKEN, *heredoc, pos));
	*heredoc += pos + eof_token_size + 1;
	return (input.size - initial_size + 3);
}

int			lex_redirection(t_array *tokens, t_slice input,
										char const **heredoc)
{
	if (input.ptr[input.size] == '<' && input.ptr[input.size + 1] == '<')
	{
		ZERO_IF_FAIL(add_token(tokens, DLESS, input.ptr + input.size, 2));
		input.size += 2;
		return (lex_heredoc(tokens, input, heredoc));
	}
	else if (input.ptr[input.size] == '<' && input.ptr[input.size + 1] == '&')
	{
		ZERO_IF_FAIL(add_token(tokens, LESSAND, input.ptr + input.size, 2));
	}
	else if (input.ptr[input.size] == '>' && input.ptr[input.size + 1] == '>')
	{
		ZERO_IF_FAIL(add_token(tokens, DGREATER, input.ptr + input.size, 2));
	}
	else if (input.ptr[input.size] == '>' && input.ptr[input.size + 1] == '&')
	{
		ZERO_IF_FAIL(add_token(tokens, GREATERAND, input.ptr + input.size, 2));
	}
	else
		return (lex_simple_redirection(tokens, input.ptr, input.size));
	return (2);
}
