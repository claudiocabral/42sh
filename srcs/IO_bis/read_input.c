/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:33 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/15 10:57:20 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	When you press [return] >
**	if a quote is not closed, if an heredoc is open or if there is a backslash
**	that the end of the line: --> it calls expand_line().
**	else, it displays the prompt a last time without the cursor, it moves down
**	the cursor, it writes in the history the new command, and it returns the
**	string to the main().
*/

char			*input_return(t_sh *sh, t_prompt **list)
{
	t_prompt	*last_char;
	char		*prompt_return;

	last_char = get_last_elem(get_last_list(*list));
	if (last_char->previous)
		last_char = last_char->previous;
	if (last_char->c != BACKSLASH && is_quote_close(get_first_list(*list)) == -1
		&& !check_heredoc(get_first_list(*list)))
	{
		display_prompt(*list, 0, 0);
		prompt_return = list_to_str(list);
		write_history(sh, list, prompt_return);
		prompt_return = interpret_heredoc(prompt_return);
		free_list(list);
		get_address_list(list, 2);
		history_reset_cursor(sh->history.history);
		reset_sh(sh);
		tputs(tgetstr("do", NULL), 1, &ft_putc);
		return (prompt_return);
	}
	expand_line(list);
	return (NULL);
}

/*
**	@return (1) if one of this moving functions has been called.
**	@return (-1) else.
*/

char			input_possibilities_move(char *input, t_prompt **list)
{
	if (!ft_strncmp(LEFT, input, 4))
		move_left(list);
	else if (!ft_strncmp(RIGHT, input, 4))
		move_right(list);
	else if (!ft_strncmp(ALT_DOWN, input, 4))
		move_down(list);
	else if (!ft_strncmp(ALT_UP, input, 4))
		move_up(list);
	else if (!ft_strncmp(ALT_LEFT, input, 4))
		word_left(list);
	else if (!ft_strncmp(ALT_RIGHT, input, 4))
		word_right(list);
	else if (!ft_strncmp(HOME, input, 4) || (input[0] == 1 && input[1] == 0))
		move_begin(list);
	else if (!ft_strncmp(END, input, 4) || (input[0] == 5 && input[1] == 0))
		move_end(list);
	else
		return (-1);
	return (1);
}

/*
**	@return (1) if one of this functions has been called.
**	@return (-1) else.
*/

static void		input_possibilities_else(char *input, t_prompt **list, t_sh *sh)
{
	if ((!ft_strncmp(SHIFT_ALT_L, input, 3) ||
		!ft_strncmp(SHIFT_ALT_R, input, 3)) && !input[3])
		copy(list, input[2], sh);
	else if (input[0] == -30 && input[1] == -105 &&
		input[2] == -118 && input[3] == 0 && sh->copy_str)
		paste(list, sh);
	else if (input[0] == -53 && input[1] == -101 && input[2] == 0)
		cut(list);
	else if (input[0] == ECHAP && input[1] == 0)
		remove_selection(*list, sh);
	else if (!ft_strncmp(DOWN, input, 4) && !(*list)->next_list)
		history_down(list, sh->history.history);
	else if (!ft_strncmp(UP, input, 4) && !(*list)->next_list)
		history_up(list, sh->history.history);
	else if (input[0] == BACKSPACE)
		delete_backspace(list);
	else if (!ft_strncmp(DELETE, input, 4))
		delete_delete(list);
	else if (input[0] == 4 && !input[1] &&
			!(*list)->previous_list && !(*list)->next)
		control_d(list);
	else if (input[0] == 12 && !input[1])
		control_l(list);
	else if (input[0] > 31 && input[1] == 0)
		add_elem(list, create_elem(input[0]));
}

/*
**	This is the main function of the line edition, at the beginning, it
**	initializes the double chained list where we will write, then we make the
**	termcap cursor invisible. And finally we read every action of the user in
**	order to change our list, until the user will press [return].
*/

char			*read_input(t_sh *sh)
{
	char		input[4];
	char		*str;
	t_prompt	*list;

	set_sh(sh);
	ft_memset(&input, 0, 4);
	list = init_list();
	get_address_list(&list, 1);
	display_prompt(list, 1, 1);
	while (read(0, input, 4))
	{
		if (input[0] == RETURN)
		{
			if ((str = input_return(sh, &list)))
				return (str);
		}
		else if (input_possibilities_move(&input[0], &list) == 1)
			;
		else
			input_possibilities_else(&input[0], &list, sh);
		get_address_list(&list, 1);
		display_prompt(list, 1, 1);
		ft_memset(&input, 0, 4);
	}
	return (NULL);
}
