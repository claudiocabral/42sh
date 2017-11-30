/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 16:58:35 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/08 15:20:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_word_length(char const *str, char c)
{
	int		size;

	while (*str)
	{
		if (*str != c)
			break ;
		++str;
	}
	size = 0;
	while (*str)
	{
		if (*str == c)
			break ;
		++size;
		++str;
	}
	return (size - 1);
}

static int		ft_count_words(char const *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str != c && *str)
			++str;
		++size;
		while (*str == c && *str)
			++str;
	}
	return (size);
}

static char		**free_words(char **word, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(word[i++]);
	free(word);
	return (0);
}

static char		**loop_strplit(char const *str, char **word,
								char separator, int nbr_words)
{
	int	i;
	int	size;

	i = 0;
	while (i < nbr_words)
	{
		size = ft_word_length(str, separator) + 1;
		if (!(word[i] = (char *)malloc(sizeof(char) * size)))
			return (free_words(word, i));
		ft_strncpy(word[i], str, size);
		str += size;
		while (*str == separator)
			++str;
		++i;
	}
	word[i] = 0;
	return (word);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**word;
	int		nbr_words;
	int		size;

	if (str == 0)
		return (NULL);
	size = 0;
	while (*str == c)
		++str;
	nbr_words = ft_count_words(str, c);
	if (!(word = (char **)malloc(sizeof(char *) * (nbr_words + 1))))
		return (NULL);
	return (loop_strplit(str, word, c, nbr_words));
}
