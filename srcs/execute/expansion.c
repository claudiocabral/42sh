/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:35:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 14:38:49 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <environment.h>
#include <ft_printf.h>
#include <execute.h>

void	change_special_char(char *str)
{
	int		i;
	char	quote;
	char	next;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (token_quote(str[i]))
		{
			if (quote == 0)
				quote = str[i];
			else
				quote = quote == str[i] ? 0 : quote;
		}
		if (str[i] == '\\' && str[i + 1])
		{
			next = str[i + 1] ? str[i + 1] : 0;
			if (special_char(next) && quote != 0)
				str[i + 1] = get_special_char(next);
			i++;
		}
		i += 1;
	}
}

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
