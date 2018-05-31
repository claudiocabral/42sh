/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:07:19 by ccabral           #+#    #+#             */
/*   Updated: 2018/05/31 04:15:29 by gfloure          ###   ########.fr       */
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

int			is_localvar(char *tmp)
{
	if (tmp && tmp[0] == 0)
	{
		free(tmp);
		return (1);
	}
	return (-1);
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

int			collect_args(t_tree **begin, t_tree **end,
							t_array *args, t_array *fds)
{
	char		*tmp;
	t_fd_pair	tmp_fd;
	int			is_only_var = 0;

	if (only_var(begin, end) == 1)
		is_only_var = 1;
	while (begin != end)
	{
		if (branch_is_redirection(*begin))
		{
			tmp_fd = redirect(*begin);
			ZERO_IF_FAIL(array_push_back(fds, &tmp_fd));
		}
		else
		{
			tmp = token_get_string((*begin)->element, is_only_var);
			if (is_localvar(tmp) == 1 && begin++)
				continue ;
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
