/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_word_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:28:33 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/21 15:42:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int						terminal_previous_word(t_terminal *terminal, int c)
{
	while (terminal->cursor != terminal->prompt_size &&
			ft_is_whitespace(terminal->line->buffer
				[terminal->cursor - terminal->prompt_size - 1]))
		terminal_move_left(terminal, c);
	while (terminal->cursor != terminal->prompt_size &&
			!ft_is_whitespace(terminal->line->buffer
				[terminal->cursor - terminal->prompt_size - 1]))
		terminal_move_left(terminal, c);
	return (1);
}

int						terminal_next_word(t_terminal *terminal, int c)
{
	while (terminal->cursor != terminal->prompt_size + (int)terminal->line->size
			&& ft_is_whitespace(terminal->line->buffer
				[terminal->cursor - terminal->prompt_size - 1]))
		terminal_move_right(terminal, c);
	while (terminal->cursor != terminal->prompt_size + (int)terminal->line->size
			&& !ft_is_whitespace(terminal->line->buffer
				[terminal->cursor - terminal->prompt_size - 1]))
		terminal_move_right(terminal, c);
	return (1);
}
