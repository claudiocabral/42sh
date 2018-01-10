/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:33:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/10 16:31:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <stdarg.h>
#include <parser.h>

int	match(t_token **token, ...)
{
	va_list	ap;
	t_tag	type;
	int		i;

	va_start(ap, token);
	i = 0;
	while ((type = va_arg(ap, t_tag)) != SENTINEL)
	{
		if ((*token)->type == type)
		{
			va_end(ap);
			++(*token);
			return (1);
		}
	}
	va_end(ap);
	return (0);
}
