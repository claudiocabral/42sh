/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:07:19 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/12 21:24:08 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <fcntl.h>
#include <unistd.h>
#include <ft_printf.h>

static int	branch_is_redirection(t_tree *tree)
{
	return (branch_equals(tree, GREATER)
			|| branch_equals(tree, DGREATER)
			|| branch_equals(tree, GREATERAND)
			|| branch_equals(tree, LESS)
			|| branch_equals(tree, DLESS)
			|| branch_equals(tree, LESSAND));
}

char		*get_tokstr(t_token *tok)
{
	char	*tmp;

	tmp = ft_strndup(tok->begin, tok->size);
	return (tmp ? tmp : NULL);
}

int			only_var(t_tree **begin, t_tree **end)
{
	char	*tmp;
	int		ret;
	t_tree	**beg;

	beg = begin;
	while (beg != end)
	{
		tmp = get_tokstr((*beg)->element);
		if ((ret = ft_strchri(tmp, '=')) == -1)
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
		beg++;
	}
	return (1);
}

int			push_if_redirection(t_tree *branch, t_array *fds)
{
	t_fd_pair	tmp_fd;

	if (!branch_is_redirection(branch))
		return (-1);
	tmp_fd = redirect(branch);
	if (tmp_fd.to == -1)
	{
		return (0);
	}
	return (array_push_back(fds, &tmp_fd) != 0);
}

int			collect_args(t_tree **begin, t_tree **end,
								t_array *args, t_array *fds)
{
	char		*tmp;
	int			is_only_var;
	int			res;

	is_only_var = only_var(begin, end);
	while (begin != end)
	{
		if ((res = push_if_redirection(*begin, fds)) == -1)
		{
			tmp = token_get_string((*begin)->element, is_only_var);
			if (is_localvar(tmp) == 1 && begin++)
				continue ;
			if (!tmp || !(array_push_back(args, &tmp)))
			{
				tmp ? free(tmp) : 0;
				array_free(args, (t_freef) & free_wrapper);
				return (0);
			}
		}
		else if (res == 0)
			return (0);
		++begin;
	}
	return (1);
}
