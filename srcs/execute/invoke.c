/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:16:45 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/04 11:02:39 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <execute.h>
#include <signal_handlers.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char	**environ;

void		invoke(char const *command)
{
	pid_t	pid;
	char	*argv[2];
	int		stat_loc;

	argv[0] = (char *)command;
	argv[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_printf("invoking\n");
		if (execve(command, argv, environ) == -1)
		{
			ft_printf("error in execve: %s not found\n", command);
			exit(0);
		}
	}
	else
		waitpid(pid, &stat_loc, 0);
}
