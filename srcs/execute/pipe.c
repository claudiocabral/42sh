/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:04:31 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 16:04:57 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_printf.h>
#include <execute.h>

int	pipe_from(char **argv, int read_write[2])
{
	close(read_write[0]);
	dup2(STDOUT_FILENO, read_write[1]);
	return (command_dispatch(argv));
}

int	pipe_to(char **argv, int read_write[2])
{
	close(read_write[1]);
	dup2(STDIN_FILENO, read_write[0]);
	return (command_dispatch(argv));
}

int	execute_pipe(char **from, char **to)
{
	int	child;
	int	read_write[2];

	if (pipe(read_write) == -1)
	{
		ft_dprintf(2, "minishell: failed to create pipe\n");
		return (0);
	}
	child = fork();
	if (child == -1)
	{
		close(read_write[0]);
		close(read_write[1]);
		ft_dprintf(2, "minishell: failed to create pipe\n");
	}
	else if (child == 0)
		pipe_from(from, read_write);
	else
		pipe_to(to, read_write);
	close(read_write[0]);
	close(read_write[1]);
	return (1);
}
