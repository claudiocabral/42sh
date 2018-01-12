/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:16:45 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 21:55:41 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
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

int		check_access(char const	*command, char const *command_name)
{
	struct stat	buff;

	if (stat(command, &buff) == -1)
	{
		ft_dprintf(2, "./minishell: command not found: %s\n", command_name);
		return (0);
	}
	if (access(command, X_OK) == -1)
	{
		ft_dprintf(2, "./minishell: permission denied: %s\n", command_name);
		return (0);
	}
	return (1);
}

int		invoke(char const *command, char **args)
{
	pid_t	pid;
	char	**env;

	if (!check_access(command, args[0]))
		return (1);
	if ((pid = fork()) == -1)
		return (1);
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
