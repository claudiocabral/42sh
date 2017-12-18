/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:10:39 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/18 16:12:54 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	token_newline(char c)
{
	return (c == '\n');
}

int	token_operator(char c)
{
	return (c == ';' || c == '&' || c == '|'
			|| c == '<' || c == '>');
}

int	token_quote(char c)
{
	return (c == '"' || c == '\'');
}


int	token_delimiter(char c)
{
	return (token_newline(c) || token_operator(c) || ft_is_whitespace(c));
}
