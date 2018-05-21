/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 13:39:29 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 11:34:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void			free_wrapper(void **ptr)
{
	free(*ptr);
}

int				ft_strncmp_wrapper(char const **a, char const **b)
{
	return (ft_strcmp_until(*a, *b, '='));
}

int				ft_strcmp_wrapper(char const **a, char const **b)
{
	return (ft_strcmp(*a, *b));
}

int				ft_strdup_wrapper(char **dst, char const *const *src,
															void *dummy)
{
	(void)dummy;
	ZERO_IF_FAIL(*dst = ft_strdup(*src));
	return (1);
}

int				ft_cpy_ptr(void **dst, void **src, void *dummy)
{
	(void)dummy;
	*dst = *src;
	return (1);
}
