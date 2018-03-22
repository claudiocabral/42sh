/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_check_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:45:39 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 16:50:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <slice.h>
#include <io.h>

int	check_complete_heredoc(t_slice eof)
{
	char	*end;

	if (!(end = ft_strrchr(eof.ptr + 1, '\n')))
		return (0);
	return (ft_strnequ(end + 1, eof.ptr, eof.size));
}
