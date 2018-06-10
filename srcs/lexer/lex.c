/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:31:42 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 04:48:02 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

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
			input += 1;
		else
			++input;
	}
	return (input);
}

static t_array		*finalize_tokens(t_array *tokens)
{
	t_token	dummy;

	dummy = emit_token(TOKEN_END, 0, 0, 0);
	if (!(array_push_back(tokens, &dummy)))
	{
		array_free(tokens, &noop);
		return (0);
	}
	return (tokens);
}

t_array				*lex(char const *input_ptr)
{
	t_array		*tokens;
	t_slice		input;
	char const	*heredoc;

	get_quote(0);
	input.ptr = input_ptr;
	input.size = 0;
	heredoc = lex_get_heredoc_pointer(input_ptr);
	if (!(tokens = array_create(sizeof(t_token), 128)))
		return (0);
	if (lex_text(tokens, input, &heredoc) == -1)
	{
		ft_dprintf(2, "lexing error\n");
		array_free(tokens, &noop);
		return (0);
	}
	return (finalize_tokens(tokens));
}
