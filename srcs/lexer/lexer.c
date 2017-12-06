/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:41:32 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/06 14:10:33 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shellma.h>
#include <array.h>

void	lex_input(t_array *tokens, char const *input)
{
	(void)tokens;
	(void)input;
}

t_array	*lex(char const *input)
{
	t_array	*tokens;

	if (!(tokens = array_create(sizeof(t_token), 128)))
		return (0);
	lex_input(tokens, input);
	return (tokens);
}
