/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:04:31 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/19 14:11:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_printf.h>
#include <tree.h>
#include <execute.h>
#include <fcntl.h>

static void	restore_stdin(int save, int pipe)
{
	close(STDIN_FILENO);
	close(pipe);
	dup2(save, STDIN_FILENO);
	close(save);
}

static int	pipe_from(t_tree *tree, int read_write[2])
{
	int	ret;

	close(read_write[0]);
	dup2(read_write[1], STDOUT_FILENO);
	ret = dispatch_branch(tree);
	exit(ret);
	return (1);
}

static int	pipe_to(t_tree *tree, int read_write[2])
{
	close(read_write[1]);
	dup2(read_write[0], STDIN_FILENO);
	return (dispatch_branch(tree));
}

int			execute_pipe(t_tree *tree)
{
	int	child;
	int	ret;
	int	read_write[2];
	int	save;

	ret = 1;
	save = dup(STDIN_FILENO);
	if (pipe(read_write) == -1)
		return (ft_dprintf(2, "21sh: failed to create pipe\n") != 0);
	if ((child = fork()) == -1)
	{
		close(read_write[0]);
		close(read_write[1]);
	}
	else if (child == 0)
		pipe_from(*(t_tree **)tree->children->begin, read_write);
	else
	{
		ret = pipe_to(*(t_tree **)(tree->children->begin
					+ sizeof(t_tree *)), read_write);
		waitpid(child, &ret, WUNTRACED);
	}
	restore_stdin(save, read_write[0]);
	return (ret);
}
