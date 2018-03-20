/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:31:42 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/20 15:09:54 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <shellma.h>
#include <lexer.h>
#include <io.h>

static char const	*skip_until_bracket(char const *input, char close)
{
	if (!*input)
		return (input);
	++input;
	while (*input)
	{
		if (*input == close)
			return (input + 1);
		++input;
	}
	return (input);
}

static char const	*lex_get_heredoc_pointer(char const *input)
{
	while (*input)
	{
		if (is_open_bracket(*input))
			input = skip_until_bracket(input,
						get_closing_bracket(*input));
		else if (input[0] == '\\' && input[1])
			input += 2;
		else if (*input == '\n')
			return (input + 1);
		else
			++input;
	}
	return (input);
}

t_array				*lex(char const *input_ptr)
{
	t_array		*tokens;
	t_slice		input;
	char const	*heredoc;


	input.ptr = input_ptr;
	input.size = 0;
	heredoc = lex_get_heredoc_pointer(input_ptr);
	if (!(tokens = array_create(sizeof(t_token), 128)))
		return (0);
	if (lex_text(tokens, input, 0) == -1)
	{
		ft_dprintf(2, "lexing error\n");
		array_free(tokens, &noop);
		return (0);
	}
	return (tokens);
}
