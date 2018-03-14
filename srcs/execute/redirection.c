/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:13:51 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/14 15:39:51 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <execute.h>
#include <token.h>

int	heredoc(t_array *args)
{
	(void)args;
	return (0);
}

int	redirect_to_fd(t_array *args, char direction)
{
	int	fd_from;
	int	fd_to;
	t_tree	**children;

	fd_from = (direction - '<') / 2;
	children = (t_tree **)args->begin;
	if (array_size(args) == 1)
	{
		fd_to = *(int *)children[0]->element;
	}
	else
	{
		fd_from = *(int *)children[0]->element;
		fd_to = *(int *)children[1]->element;
	}
	if (direction == '>')
		return (dup2(fd_from, fd_to));
	return (dup2(fd_to, fd_from));
}

int	redirect_to_file(t_array *args, int mode, char direction)
{
	int		fd;
	int		fd_from;
	char	*path;
	t_tree	**children;

	fd_from = (direction - '<') / 2;
	children = (t_tree **)args->begin;
	if (array_size(args) == 1)
		path = (char *)children[0]->element;
	else
	{
		fd_from = *(int*)children[0]->element;
		path = (char *)(children[1])->element;
	}
	if ((fd = open(path, mode) < 0))
		return (0);
	if (direction == '>')
		dup2(fd_from, fd);
	else
		dup2(fd, fd_from);
	return (fd);
}

int	redirect(t_tree *tree)
{
	if (branch_equals(tree, GREATER))
		redirect_to_file(tree->children, O_RDWR | O_TRUNC | O_CREAT, '>');
	else if (branch_equals(tree, LESS))
		redirect_to_file(tree->children, O_RDWR | O_TRUNC | O_CREAT, '<');
	else if (branch_equals(tree, GREATERAND))
		redirect_to_fd(tree->children, '>');
	else if (branch_equals(tree, LESSAND))
		redirect_to_fd(tree->children, '<');
	else if (branch_equals(tree, DGREATER))
		redirect_to_file(tree->children, O_RDWR | O_APPEND | O_CREAT, '<');
	else if (branch_equals(tree, DLESS))
		heredoc(tree->children);
	return (1);
}
