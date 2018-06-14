/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:57:08 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/13 11:10:24 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	remove_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			ft_memmove(&str[i], &str[i] + sizeof(char), ft_strlen(&str[i]));
			if (!str[i])
				break ;
		}
		i++;
	}
}

int		remove_quotes(char *str)
{
	int	size;

	if (*str != '"' && *str != '\'' && *str != '`')
		return (-1);
	size = ft_strlen(str);
	ft_memmove(str, str + sizeof(char), size);
	str[size - 1] = 0;
	return (1);
}

void	remove_bquote(char *token)
{
	int		i;
	int		y;

	i = 0;
	while (token[i])
	{
		if (token[i] && token[i] == '\\')
			i += 2;
		if ((size_t)i > ft_strlen(token) || !token[i])
			break ;
		if (token[i] && token[i] == '`')
		{
			y = i + 1;
			y = skip_until_equals(token, y, i);
			if (token[y] == token[i])
			{
				remove_quotes(&token[y]);
				remove_quotes(&token[i]);
				i = y - 2;
			}
		}
		i++;
	}
}
