/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:39:10 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:40:19 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <token.h>
#include <execute.h>

char		*token_get_string(t_token *token)
{
	char	*str;

	if (token->begin)
		str = ft_strndup(token->begin, token->size);
	else
		str = ft_strdup("");
	if (!str)
		return (0);
	remove_backslash(str);
	ZERO_IF_FAIL(str = expand(str));
	remove_quotes(str);
	return (str);
}

int			token_get_int(t_token *token)
{
	char	*str;
	int		nbr;

	ZERO_IF_FAIL(str = token_get_string(token));
	nbr = ft_atoi(str);
	free(str);
	return (nbr);
}
