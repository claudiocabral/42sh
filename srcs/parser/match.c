/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:33:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/07 14:46:17 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <stdarg.h>
#include <parser.h>

int	peek_impl(t_token **token, va_list *ap)
{
	t_tag	type;

	while ((type = va_arg(*ap, t_tag)) != SENTINEL)
	{
		if ((*token)->type == type)
			return (1);
	}
	return (0);
}

int	match(t_token **token, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, token);
	if ((ret = peek_impl(token, &ap)))
		++(*token);
	va_end(ap);
	return (ret);
}

int	peek(t_token **token, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, token);
	ret = peek_impl(token, &ap);
	va_end(ap);
	return (ret);
}
