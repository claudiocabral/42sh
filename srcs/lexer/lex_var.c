/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 16:51:31 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 16:57:54 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int			lex_quote(t_array *tokens, t_slice input, int posb)
{
	int		pos;

	pos = posb + 1;
	while ((input.ptr[pos]) && ((input.ptr[pos] != input.ptr[posb])))
	{
		if (input.ptr[pos++] == '\\')
			pos++;
	}
	if (input.ptr[pos] != input.ptr[posb])
		return (-1);
	if (token_quote(input.ptr[pos + 1] || token_var(input.ptr[pos + 1])) ||
			!token_delimiter(input.ptr[pos + 1]))
		return (lex_token(tokens, input, pos + 1));
	else if (add_token(tokens,
				TOKEN, input.ptr + input.size, pos - input.size + 1))
		return (pos + 1);
	return (-1);
}

int			lex_var(t_array *tokens, t_slice input, int posb)
{
	int	pos;

	pos = posb + 1;
	while ((input.ptr[pos]) && ((input.ptr[pos] != input.ptr[input.size])))
	{
		if (!ft_isalnum(input.ptr[pos]))
			break ;
		pos++;
	}
	if (input.ptr[pos] && (token_quote(input.ptr[pos])
			|| token_var(input.ptr[pos]) || !token_delimiter(input.ptr[pos])))
		return (lex_token(tokens, input, pos));
	else if (add_token(tokens, TOKEN, input.ptr + input.size, pos - input.size))
		return (pos);
	return (-1);
}

int			lex_semicolon(t_array *tokens, t_slice input)
{
	if (input.ptr[input.size + 1] != ';')
		return (add_token(tokens, SEMICOLON, input.ptr + input.size, 1));
	return (add_token(tokens, DSEMI, input.ptr + input.size, 2));
}
