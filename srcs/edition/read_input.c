/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:33 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/04 03:44:34 by gfloure          ###   ########.fr       */
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
	if ((last_char->c != BACKSLASH || (last_char->c == BACKSLASH &&
		last_char->previous && last_char->previous->c == BACKSLASH)) &&
		is_quote_close(get_first_list(*list)) == -1 &&
		!check_heredoc(get_first_list(*list)))
	{
		display_prompt(*list, 0, 0);
		prompt_return = list_to_str(list);
		write_history(sh, list, prompt_return);
		free_list(list);
		get_address_list(list, 2);
		history_reset_cursor(sh->history.history);
		reset_sh(sh);
		tputs(tgetstr("do", NULL), 1, &ft_putc);
		// ft_printf("STR = %s\n", prompt_return);
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
	if ((input[0] == -61 && input[1] == ALT_A) ||
		(input[0] == -30 && input[1] == -120 && input[2] == ALT_D))
		copy(list, input[2], sh);
	else if (input[0] == -30 && input[1] == -120 && input[2] == ALT_V
			&& sh->copy_str)
		paste(list, sh);
	else if (input[0] == -30 && input[1] == -119 && input[2] == ALT_X)
		cut(list);
	else if (input[0] == 4 && !input[1] &&
		!(*list)->previous_list && !(*list)->next)
		control_d(list)	;
	else if (input[0] == -61 && input[1] == ALT_S)
		remove_selection(*list, sh);
	else if (!ft_strncmp(DOWN, input, 4) && !(*list)->next_list)
		history_down(list, sh->history.history);
	else if (!ft_strncmp(UP, input, 4) && !(*list)->next_list)
		history_up(list, sh->history.history);
	else if (input[0] == BACKSPACE)
		delete_backspace(list);
	else if (!ft_strncmp(DELETE, input, 4) || (input[0] == 4 && input[1] == 0))
		delete_delete(list);
	else if (input[0] == 11 && input[1] == 0)
		control_k(list);
	else if (input[0] == 21 && input[1] == 0)
		control_u(list);
	else if (input[0] == 23 && input[1] == 0)
		control_w(list);
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

	ft_memset(&input, 0, 4);
	ZERO_IF_FAIL(list = init_list());
	get_address_list(&list, 1);
	display_prompt(list, 1, 1);
	while (read(0, &input, 1))
	{
		if (input[0] == '\e' || input[0] == -30 || input[0] == -61)
			read(0, &input[1], 3);
		// ft_putnbr(input[0]);
		// ft_putchar('\n');
		// ft_putnbr(input[1]);
		// ft_putchar('\n');
		// ft_putnbr(input[2]);
		// ft_putchar('\n');
		// ft_putnbr(input[3]);
		// ft_putchar('\n');
		if ((input[0] == TAB && input[1] == 0) || (sh->completion &&
				(input[0] == ECHAP || (input[0] == RETURN && input[1] == 0))))
			input_autocompletion(&input[0], &list, sh->completion);
		else if (input[0] == RETURN)
		{
			if ((str = input_return(sh, &list)))
				return (str);
		}
		else
		{
			free_autocompletion(sh);
			if (input_possibilities_move(&input[0], &list) == 1)
				;
			else
				input_possibilities_else(&input[0], &list, sh);
		}
		get_address_list(&list, 1);
		display_prompt(list, 1, 1);
		ft_memset(&input, 0, 4);
	}
	return (NULL);
}
