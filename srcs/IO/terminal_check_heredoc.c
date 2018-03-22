/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_check_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:39 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 19:01:08 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <slice.h>
#include <io.h>

int	check_complete_heredoc(t_slice eof, char const **line)
{
	if (*line < eof.ptr)
		*line = eof.ptr;
	if (!(*line = ft_strchr(*line, '\n')))
		return (0);
	if ((*line = slice_find((char *)*line, eof)))
		return (1);
	return (0);
}
