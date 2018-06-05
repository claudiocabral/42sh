/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:10:39 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/04 02:25:26 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	token_newline(char c)
{
	return (c == '\n');
}

int	token_operator(char c)
{
	return ((get_quote(-42) == 0) && (c == ';' || c == '&' || c == '|'
			|| c == '<' || c == '>' || c == '`'));
}

int	token_comment(char c)
{
	return (c == '#');
}

int	token_white_space(int c)
{
	int		backup;

	backup = get_quote(-42);
	if (c == '\'' || c == '"' || c == '`')
	{
		backup == 0 ? get_quote(c) : 0;
		backup == c ? get_quote(0) : 0;
	}
	if (ft_is_whitespace(c) && backup == 0)
		return (1);
	return (0);
}

int	token_delimiter(char c)
{
	return (token_newline(c) || token_operator(c) || token_white_space(c));
}
