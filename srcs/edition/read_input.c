/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:33 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/13 11:09:53 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

int				is_backslash(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if ((size_t)i < ft_strlen(str) && str[i] == '\\' && str[i + 1])
			i += 1;
		else if (str[i] == '\\' && !str[i + 1])
		{
			free(str);
			return (42);
		}
		if (!str[i] && !str[i + 1])
		{
			free(str);
			return (-1);
		}
		i++;
	}
	free(str);
	return (-1);
}

char			*list_to_str_all(t_prompt **list)
{
	t_prompt		*tmp;
	unsigned int	i;
	char			*str;

	tmp = get_first_list(*list);
	i = return_str_len(tmp);
	if (!(str = ft_strnew(i + 32)))
		return (NULL);
	ft_bzero(str, i + 32);
	i = 0;
	while (tmp)
	{
		if (!tmp->insertion && tmp->cs == 0)
			str[i++] = tmp->c;
		if (tmp && !tmp->next)
			tmp = tmp->next_list;
		else
			tmp = tmp->next;
	}
	return (str);
}

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
	char		*prompt_return;

	if (is_backslash(list_to_str_all(list)) == -1 &&
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
		return (prompt_return);
	}
	expand_line(list);
	return (NULL);
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
		if (input[0] == '\e')
			read(0, &input[1], 3);
		if ((str = run_action(sh, &list, &input[0])) != NULL)
			return (str);
		get_address_list(&list, 1);
		display_prompt(list, 1, 1);
		ft_memset(&input, 0, 4);
	}
	return (NULL);
}
