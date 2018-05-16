/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/23 16:27:52 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void	exit_shell(t_sh *sh)
{
	reset_sh(sh);
	if (sh->history.fd_history != -1)
		close(sh->history.fd_history);
	exit(0);
}

void	init_sh(t_sh *sh)
{
	char	input_tmp;

	if (sh != NULL)
	{
		init_term(sh);
		g_sh = sh;
		ioctl(0, TIOCSTI, "0");
		if (read(0, &input_tmp, 1) == -1)
			exit_shell(sh);
		sh->history.fd_history = open_history_file();
		sh->history.history = history_file_to_list(sh->history.fd_history);
		sh->heredoc_delim = NULL;
	}
}

int				interactive_session(void)
{
	t_sh			sh;

	g_sh = &sh;
	init_sh(&sh);
	while (1)
	{
		set_sh(&sh);
		signal_init();
		process_input(read_input(&sh));
	}
}
