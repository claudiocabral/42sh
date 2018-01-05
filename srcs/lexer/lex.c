/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:31:42 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 11:35:39 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <shellma.h>
#include <lexer.h>

t_array		*lex(char const *input)
{
	t_array	*tokens;

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
