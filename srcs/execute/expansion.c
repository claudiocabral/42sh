/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:35:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 18:43:53 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <environment.h>

void	remove_backslash(char *str)
{
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

char	*expand_env(char *value)
{
	char	*str;

	str = ft_getenv(value + 1);
	free(value);
	return (str ? ft_strdup(str) : ft_strdup(""));
}

char	*expand(char *value)
{
	size_t	size;
	char	*str;

	size = 0;
	str = value;
	if (ft_strncmp(value, "~/", 2) == 0)
	{
		size = ft_strlen(ft_getenv("HOME")) + ft_strlen(value);
		if (!(str = (char *)malloc(sizeof(char) * size)))
		{
			free(value);
			return (0);
		}
		str[0] = 0;
		ft_strcat(str, ft_getenv("HOME"));
		ft_strcat(str, "/");
		ft_strcat(str, value + 2);
		free(value);
	}
	else if (ft_strcmp(value, "~") == 0)
	{
		free(value);
		str = ft_strdup(ft_getenv("HOME"));
	}
	return (str[0] == '$' && str[1] ? expand_env(str) : str);
}
