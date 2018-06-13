/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:19:54 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/13 05:32:28 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

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

char			input_possibilities_control(char *input, t_prompt **list)
{
	if (input[0] == 4 && !input[1] && !(*list)->previous_list && !(*list)->next)
		control_d(list)	;
	else if (input[0] == 11 && input[1] == 0)
		control_k(list);
	else if (input[0] == 21 && input[1] == 0)
		control_u(list);
	else if (input[0] == 23 && input[1] == 0)
		control_w(list);
	else if (input[0] == 12 && !input[1])
		control_l(list);
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
	if ((input[0] == CTRL_N || input[0] == CTRL_P) && input[1] == 0)
		copy(list, input[0], sh);
	else if (input[0] == CTRL_V && input[1] == 0 && sh->copy_str)
		paste(list, sh);
	else if (input[0] == CTRL_X && input[1] == 0)
		cut(list);
	else if (input[0] == CTRL_R && input[1] == 0)
		remove_selection(*list, sh);
	else if (!ft_strncmp(DOWN, input, 4) && !(*list)->next_list)
		history_down(list, sh->history.history);
	else if (!ft_strncmp(UP, input, 4) && !(*list)->next_list)
		history_up(list, sh->history.history);
	else if (input[0] == BACKSPACE)
		delete_backspace(list);
	else if (!ft_strncmp(DELETE, input, 4) || (input[0] == 4 && input[1] == 0))
		delete_delete(list);
	else if (input[0] > 31 && input[1] == 0)
		add_elem(list, create_elem(input[0]));
}

char			*run_action(t_sh *sh, t_prompt **list, char *input)
{
	char	*str;

	if ((input[0] == TAB && input[1] == 0) || (sh->completion &&
		(input[0] == ECHAP || (input[0] == RETURN && input[1] == 0))))
		input_autocompletion(&input[0], list, sh->completion);
	else if (input[0] == RETURN && input[1] == 0)
	{
		if ((str = input_return(sh, list)))
			return (str);
	}
	else
	{
		free_autocompletion(sh);
		if (input_possibilities_move(&input[0], list) == 1)
			;
		else if (input_possibilities_control(&input[0], list) == 1)
			;
		else
			input_possibilities_else(&input[0], list, sh);
	}
	return (NULL);
}
