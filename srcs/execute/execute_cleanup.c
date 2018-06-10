/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:21:14 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 14:21:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <array.h>
#include <execute.h>

static void	close_fd_pair(t_fd_pair *fd, void *args)
{
	(void)args;
	close(fd->from);
	if (fd->to > -1)
	{
		dup2(fd->to, fd->from);
		close(fd->to);
	}
}

void		execute_cleanup(t_array *fds, t_array *args, t_array *args_copy)
{
	if (fds)
	{
		array_apply_reverse(fds, 0, (t_applyf) & close_fd_pair);
		array_free(fds, (t_freef) & noop);
	}
	if (args_copy)
	{
		array_free(args_copy, (t_freef) & free_wrapper);
	}
	if (args)
	{
		free(args->begin);
		free(args);
	}
}
