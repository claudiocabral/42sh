/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <clement@trosa.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:15:30 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/27 20:46:45 by iomonad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdarg.h>

#undef MAXARG
#define MAXARG 100

static size_t	get_args(size_t n, va_list *ap, char *bufarg[])
{
	size_t	i;
	size_t	total;
	char	*tmp;

	i = 0;
	total = 0;
	while (i < n && i < MAXARG)
	{
		tmp = va_arg(*ap, char *);
		total += ft_strlen(tmp);
		bufarg[i] = tmp;
		i += 1;
	}
	return (total);
}

char			*ft_vjoin(size_t n, ...)
{
	size_t	total;
	size_t	i;
	va_list	ap;
	char	*res;
	char	*bufarg[MAXARG];

	va_start(ap, n);
	total = get_args(n, &ap, bufarg);
	va_end(ap);
	if (!(res = (char *)malloc(sizeof(char) * (total + 1))))
		return (NULL);
	*res = '\0';
	i = 0;
	while (i < n && i < MAXARG)
	{
		ft_strcat(res, bufarg[i]);
		i += 1;
	}
	return (res);
}
