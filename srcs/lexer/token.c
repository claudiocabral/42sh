/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:23:34 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:52:51 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <lexer.h>
#include <token.h>

t_token		emit_token(t_tag type, char const *input, int start, int end)
{
	t_token	token;

	token.type = type;
	token.begin = input + start;
	token.size = end - start;
	return (token);
}

void		fill_token(t_token *token, t_tag type, char const *begin,
															size_t size)
{
	token->type = type;
	token->begin = begin;
	token->size = size;
}
