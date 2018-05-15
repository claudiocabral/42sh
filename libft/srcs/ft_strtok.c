/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:16 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/11 11:46:53 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char		*split_delimiters(char *str, char *delim)
{
	int			m;
	int			i;
	char		s;
	char		d;

	s = (str != NULL) ? *str : 0;
	while (s)
	{
		m = 0;
		i = 0;
		while ((d = delim[i++]) != '\0')
			if (s == d)
				m = 1;
		if (m == 0)
			return (str);
		s = *++str;
	}
	return (NULL);
}

char			*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*ps;
	char		*ret;
	int			i;

	s = (str) ? str : s;
	if (!s || *s == '\0' || (s = split_delimiters(s, (char*)delim)) == NULL)
		return (NULL);
	ps = s;
	while (*ps)
	{
		i = 0;
		while (delim[i])
			if (*ps == delim[i++])
			{
				*ps = '\0';
				ret = s;
				s = split_delimiters(ps + 1, (char*)delim);
				return (ret);
			}
		++ps;
	}
	ret = s;
	s = ps;
	return (ret);
}
