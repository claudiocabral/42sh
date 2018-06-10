/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:16:45 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 14:31:34 by ccabral          ###   ########.fr       */
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
	int		stat_loc;
	char	*res;

	waitpid(pid, &stat_loc, 0);
	if ((WIFSIGNALED(stat_loc)))
		write(0, "\n", 1);
	if ((res = ft_itoa(WEXITSTATUS(stat_loc))))
	{
		ft_setenv("?", res, 1);
		free(res);
	}
	return (stat_loc);
}

int		check_access(char const *command, char const *command_name,
														char const *who)
{
	struct stat	buff;

	if (!command || stat(command, &buff) == -1)
	{
		ft_dprintf(2, "%s: command not found: %s\n", who, command_name);
		return (0);
	}
	if ((buff.st_mode & S_IFDIR) || access(command, X_OK) == -1)
	{
		ft_dprintf(2, "%s: permission denied: %s\n", who, command_name);
		return (0);
	}
	return (1);
}

int		invoke(char const *command, char **args, char **env, char const *who)
{
	pid_t	pid;

	if (!check_access(command, args[0], who))
		return (1);
	if ((pid = fork()) == -1)
		return (1);
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
