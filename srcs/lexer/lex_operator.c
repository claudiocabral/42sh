/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:56:11 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:37:40 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	lex_simple_redirection(t_array *tokens, char const *input,
																int start)
{
	if (input[start] == '<')
		ZERO_IF_FAIL(add_token(tokens, LESS, input + start, 1));
	else if (input[start] == '>')
		ZERO_IF_FAIL(add_token(tokens, GREATER, input + start, 1));
	else
		return (0);
	return (1);
}

int			lex_redirection(t_array *tokens, char const *input, int start)
{
	if (input[start] == '<' && input[start + 1] == '<')
		ZERO_IF_FAIL(add_token(tokens, DLESS, input + start, 2));
	else if (input[start] == '<' && input[start + 1] == '&')
		ZERO_IF_FAIL(add_token(tokens, LESSAND, input + start, 2));
	else if (input[start] == '>' && input[start + 1] == '>')
		ZERO_IF_FAIL(add_token(tokens, DGREATER, input + start, 2));
	else if (input[start] == '>' && input[start + 1] == '&')
		ZERO_IF_FAIL(add_token(tokens, GREATERAND, input + start, 2));
	else
		return (lex_simple_redirection(tokens, input, start));
	return (2);
}
