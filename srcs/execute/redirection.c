/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:13:51 by ccabral           #+#    #+#             */
/*   Updated: 2018/05/31 02:38:55 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <execute.h>
#include <token.h>

t_fd_pair	make_redirection(t_fd_pair fd)
{
	int	tmp;

	tmp = dup(fd.from);
	dup2(fd.to, fd.from);
	fd.to = tmp;
	return (fd);
}

t_fd_pair	heredoc(t_token *token)
{
	t_fd_pair	fd;
	int			read_write[2];

	fd.to = dup(STDIN_FILENO);
	pipe(read_write);
	dup2(read_write[0], STDIN_FILENO);
	close(read_write[0]);
	fd.from = STDIN_FILENO;
	write(read_write[1], token->begin, token->size);
	close(read_write[1]);
	return (fd);
}

t_fd_pair	redirect_to_fd(t_array *args, char direction)
{
	t_fd_pair	fd;
	t_tree		**children;

	fd.from = (direction - '<') / 2;
	fd.to = -1;
	children = (t_tree **)args->begin;
	if (array_size(args) == 1)
	{
		if (check_agreggator((t_token *)children[0]->element) < 0)
			return (deal_with_aggregator(fd));
		else
			fd.to = token_get_int((t_token *)children[0]->element);
	}
	else
	{
		fd.from = token_get_int((t_token *)children[0]->element);
		if (check_agreggator((t_token *)children[1]->element) < 0)
			return (deal_with_aggregator(fd));
		else
			fd.to = token_get_int((t_token *)children[1]->element);
	}
	if (direction == '<')
		swap_fd(&fd);
	return (make_redirection(fd));
}

t_fd_pair	redirect_to_file(t_array *args, int mode, char direction)
{
	t_fd_pair	fd;
	char		*path;
	t_tree		**children;
	int			tmp;

	fd.from = (direction - '<') / 2;
	children = (t_tree **)args->begin;
	if (array_size(args) == 1)
		path = token_get_string((t_token *)children[0]->element, 0);
	else
	{
		fd.from = token_get_int((t_token *)children[0]->element);
		path = token_get_string((t_token *)children[1]->element, 0);
	}
	if (!path)
		fd.to = -1;
	else
		fd.to = open(path, mode, 0644);
	free(path);
	if (fd.to < 0)
		return (fd);
	tmp = fd.to;
	fd = make_redirection(fd);
	close(tmp);
	return (fd);
}

t_fd_pair	redirect(t_tree *tree)
{
	t_fd_pair	ret;

	ret.to = -1;
	ret.from = -1;
	if (branch_equals(tree, GREATER))
		ret = redirect_to_file(tree->children, O_RDWR | O_TRUNC | O_CREAT, '>');
	else if (branch_equals(tree, DGREATER))
		ret = redirect_to_file(tree->children,
				O_RDWR | O_APPEND | O_CREAT, '>');
	else if (branch_equals(tree, GREATERAND))
		ret = redirect_to_fd(tree->children, '>');
	else if (branch_equals(tree, LESS))
		ret = redirect_to_file(tree->children, O_RDONLY, '<');
	else if (branch_equals(tree, DLESS))
		ret = heredoc((t_token *)
				(((t_tree **)tree->children->begin)[0])->element);
	else if (branch_equals(tree, LESSAND))
		ret = redirect_to_fd(tree->children, '<');
	return (ret);
}
