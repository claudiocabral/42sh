/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:16:45 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 11:57:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal_handlers.h>
#include <signal.h>
#include <ft_printf.h>
#include <execute.h>
#include <environment.h>

int		invoke_builtin(t_builtin const *command, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (command->func(i, args));
}

int		wait_process(pid_t pid)
{
	int	stat_loc;
	int	sig;

	waitpid(pid, &stat_loc, 0);
	if ((sig = interrupt_handler(0)))
	{
		kill(pid, sig);
		write(0, "^C\n", 3);
	}
	return (stat_loc);
}

int		invoke(char const *command, char **args)
{
	pid_t	pid;
	char	**env;

	pid = fork();
	env = get_environment();
	if (pid == 0)
	{
		if (execve(command, args, env) == -1)
		{
			ft_dprintf(2, "error in execve\n", command);
			exit(1);
		}
	}
	return (wait_process(pid));
}
