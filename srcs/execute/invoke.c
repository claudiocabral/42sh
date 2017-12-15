/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:16:45 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 11:54:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal_handlers.h>
#include <ft_printf.h>
#include <execute.h>
#include <environment.h>

void		invoke(char const *command, char **args)
{
  pid_t pid;
  int stat_loc;

  pid = fork();
  if (pid == 0) {
	  if (execve(command, args, get_environment()) == -1) {
		  ft_dprintf(2, "error in execve: %s not found\n", command);
		  exit(0);
	  }
  }
  else
	  waitpid(pid, &stat_loc, 0);
}
