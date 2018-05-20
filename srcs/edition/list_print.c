/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:33:55 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 13:33:57 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	'cr': termcaps to move the cursor at the beginning of the line.
**	'cd: termcaps to clear the line and all the lines below.
**	Then we print lists, and if the the char adj_cursor is not 0, we adjust the
**	cursor to the line of the prompt.
*/

void	display_prompt(t_prompt *list, char with_options, char adj_cursor)
{
	tputs(tgetstr("cr", NULL), 1, &ft_putc);
	tputs(tgetstr("cd", NULL), 1, &ft_putc);
	print_all_list(list, with_options);
	if (adj_cursor)
		adjust_cursor(list);
}

void	basic_prompt(t_prompt *list)
{
	char *cwd;

	ft_putstr(" ");
	ft_putstr("\e[36m");
	list->prompt_len = 5;
	if ((cwd = getcwd(NULL, 0)))
	{
		if (ft_strlen(cwd) == 1)
			ft_putchar('/');
		else
			ft_putstr(ft_strrchr(cwd, '/') + 1);
		list->prompt_len += ft_strlen(cwd) == 1 ? 1 :
			ft_strlen(ft_strrchr(cwd, '/') + 1);
		ft_strdel(&cwd);
	}
	ft_printf("%s $> ", RESET);
}

void	print_prompt(t_prompt *list)
{
	if (list->prompt_type == MULTI_LINE)
		write(1, "> ", 2);
	else if (list->prompt_type == QUOTE)
		write(1, "quote> ", 7);
	else if (list->prompt_type == DQUOTE)
		write(1, "dquote> ", 8);
	else if (list->prompt_type == HEREDOC)
		write(1, "heredoc> ", 9);
	else
		basic_prompt(list);
}

void	print_all_list(t_prompt *list, char with_options)
{
	t_prompt		*tmp;

	tmp = get_first_list(list);
	while (tmp)
	{
		print_prompt(tmp);
		print_list(tmp, with_options);
		if (tmp && get_last_elem(tmp)->c != RETURN && tmp->next_list)
			write(1, "\n", 1);
		tmp = tmp->next_list;
	}
}

void	print_list(t_prompt *list, char with_options)
{
	t_prompt		*tmp;

	tmp = list;
	while (tmp)
	{
		if (with_options && tmp->cursor)
			ft_putstr_fd(REVERSE_VIDEO, 1);
		if (with_options && tmp->selected)
			ft_putstr_fd(GREEN_FG, 1);
		ft_putchar_fd(tmp->c, 1);
		if ((with_options && tmp->cursor) || (with_options && tmp->selected))
			ft_putstr_fd(RESET, 1);
		tmp = tmp->next;
	}
}
