/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:04:31 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/09 17:49:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_printf.h>
#include <execute.h>
#include <tree.h>

int	pipe_from(t_tree *tree, int read_write[2])
{
	close(read_write[0]);
	dup2(STDOUT_FILENO, read_write[1]);
	return (execute_simple_command(tree));
}

int	pipe_to(t_tree *tree, int read_write[2])
{
	close(read_write[1]);
	dup2(STDIN_FILENO, read_write[0]);
	return (execute_simple_command(tree));
}

int	execute_pipe(t_tree	*tree)
{
	int	child;
	int	ret;
	int	read_write[2];

	ret = 1;
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
		pipe_from(*(t_tree **)tree->children->begin, read_write);
	else
	{
		waitpid(child, &ret, WUNTRACED);
		if (!ret)
			ret = pipe_to(*(t_tree **)tree->children->begin
					+ sizeof(t_tree), read_write);
	}
	close(read_write[0]);
	close(read_write[1]);
	return (ret);
}
