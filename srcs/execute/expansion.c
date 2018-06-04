/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:35:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/04 01:13:59 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <environment.h>
#include <ft_printf.h>

void	remove_backslash(char *str)
{
	if (*str == '"' || *str == '\'')
		return ;
	while (*str)
	{
		if (*str == '\\')
		{
			if (str[1] == '\n')
				ft_memmove(str, str + sizeof(char) * 2, ft_strlen(str));
			else
				ft_memmove(str, str + sizeof(char), ft_strlen(str));
			if (!*str)
				break ;
		}
		++str;
	}
}

int		remove_quotes(char *str)
{
	int	size;

	if (*str != '"' && *str != '\'')
		return (-1);
	size = ft_strlen(str);
	ft_memmove(str, str + sizeof(char), size);
	str[size - 1] = 0;
	return (1);
}

char	*expand_env(char *value)
{
	char	*str;

	str = ft_getenv_safe(value + 1);
	free(value);
	return (str ? ft_strdup(str) : ft_strdup(""));
}

char	*expand(char *value)
{
	size_t	size;
	char	*str;

	str = value;
	if (ft_strncmp(value, "~/", 2) == 0)
	{
		size = ft_strlen(ft_getenv_safe("HOME")) + ft_strlen(value);
		if (!(str = (char *)malloc(sizeof(char) * size)))
		{
			free(value);
			return (0);
		}
		str[0] = 0;
		ft_strcat(str, ft_getenv_safe("HOME"));
		ft_strcat(str, "/");
		ft_strcat(str, value + 2);
		free(value);
	}
	else if (ft_strcmp(value, "~") == 0)
	{
		free(value);
		ZERO_IF_FAIL(str = ft_strdup(ft_getenv_safe("HOME")));
	}
	return (str);
}
