/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:33:10 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:35:19 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

void			*median(void *begin, void *end, size_t size)
{
	return (begin + ((size_t)(end - begin) / (size * 2)) * size);
}
