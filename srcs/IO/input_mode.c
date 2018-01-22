/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:48:36 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/22 18:36:42 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_printf.h>

int	terminal_backslash(t_terminal *terminal, int c)
{
	terminal_insert(terminal, c);
	terminal->input_mode = BACKSLASH_INPUT;
	return (1);
}

int	terminal_backslash_input(t_terminal *terminal, char c[16], int size)
{
	int	ret;

	if (size > 1 || (unsigned char)c[0] >= 128)
		ret = handle_string_input(terminal, c);
	else if (*c == '\n')
	{
		ret = terminal_insert(terminal, *c);
	}
	else
		ret = handle_regular_input(terminal, *c);
	terminal->input_mode = NORMAL_INPUT;
	terminal->prompt_pointer = terminal->prompt;
	return (ret);
}
