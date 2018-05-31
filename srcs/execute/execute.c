/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:50:24 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/31 03:51:25 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <shellma.h>
#include <execute.h>
#include <signal_handlers.h>
#include <ft_printf.h>
#include <token.h>
#include <environment.h>
#include <localvar.h>

int		command_dispatch(char **argv, char **env, char const *who)
{
	void const	*tmp;

	if (!argv[0])
		return (-1);
	if (ft_strchr(argv[0], '/'))
		return (invoke(argv[0], argv, env, who));
	if ((tmp = get_builtin_command(argv[0])))
		return (invoke_builtin(tmp, argv));
	return (invoke(command_name_lookup(argv[0]), argv, env, who));
}

int		execute_simple_command(t_tree *tree)
{
	t_array		*args;
	t_array		*args_copy;
	t_array		*fds;
	int			ret;

	if (!(args = array_create(sizeof(char *), 16)))
		return (1);
	if (!(fds = array_create(sizeof(t_fd_pair), 16)))
	{
		array_free(args, (t_freef) & noop);
		return (1);
	}
	if (!collect_args((t_tree **)tree->children->begin,
				(t_tree **)tree->children->end, args, fds))
		return (1);
	if (!(args_copy = array_copy(
			args, 0, (t_cpyf) & ft_cpy_ptr, (t_freef) & free_wrapper)))
	{
		array_free(args, (t_freef) & free_wrapper);
		return (1);
	}
	ret = command_dispatch((char **)args->begin, get_environment(),
			"./42sh");
	execute_cleanup(fds, args, args_copy);
	return (ret);
}

int		execute_commands(t_tree *tree)
{
	t_tree		**child;
	int			ret;

	child = (t_tree **)tree->children->begin;
	ret = 0;
	while (child != tree->children->end)
	{
		token_var_valid(0);
		if (*child)
			ret = execute_simple_command(*child);
		++child;
	}
	return (ret);
}

int		execute(t_tree *tree)
{
	int	ret;

	if (!tree)
		return (0);
	ret = dispatch_branch(tree);
	tree_free(tree, (t_freef) & noop);
	return (ret);
}
