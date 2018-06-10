/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:52:12 by mprevot           #+#    #+#             */
/*   Updated: 2018/06/10 13:52:14 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <slice.h>

int			lex_comment(t_slice input)
{
	int	pos;

	pos = input.size + 1;
	while (input.ptr[pos] && input.ptr[pos] != '\n')
		++pos;
	return (pos);
}
