/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:07:19 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/20 17:32:32 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <fcntl.h>
#include <unistd.h>

static int	branch_is_redirection(t_tree *tree)
{
	return (branch_equals(tree, GREATER)
			|| branch_equals(tree, DGREATER)
			|| branch_equals(tree, GREATERAND)
			|| branch_equals(tree, LESS)
			|| branch_equals(tree, DLESS)
			|| branch_equals(tree, LESSAND));
}

int			collect_args(t_tree **begin, t_tree **end,
							t_array *args, t_array *fds)
{
	char		*tmp;
	t_fd_pair	tmp_fd;

	while (begin != end)
	{
		if (branch_is_redirection(*begin))
		{
			tmp_fd = redirect(*begin);
			ZERO_IF_FAIL(array_push_back(fds, &tmp_fd));
		}
		else
		{
			tmp = token_get_string((*begin)->element);
			if (!tmp || !(array_push_back(args, &tmp)))
			{
				free(tmp);
				array_free(args, (t_freef) & free_wrapper);
				return (0);
			}
		}
		++begin;
	}
	return (1);
}
