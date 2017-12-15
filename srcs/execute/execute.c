/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:50:24 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 16:24:29 by claudioca        ###   ########.fr       */
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

char	*token_get_value(t_token *token)
{
	if (token->begin)
		return (ft_strndup(token->begin, token->size));
	return (ft_strdup(""));
}

int		command_dispatch(char **argv)
{
	void const	*tmp;

	if (ft_strchr(argv[0], '/'))
		return (invoke(argv[0], argv));
	if ((tmp = get_builtin_command(argv[0])))
		return (invoke_builtin(tmp, argv));
	if ((tmp = command_name_lookup(argv[0])))
		return (invoke(tmp, argv));
	ft_dprintf(2, "minishell: command not found: %s\n", argv[0]);
	return (127);
}

int		execute_simple_command(t_tree *tree)
{
	t_array		*args;
	t_tree		**child;
	void const	*tmp;
	int			ret;

	if (!(args = array_create(sizeof(char *), 16)))
		return (1);
	child = (t_tree **)tree->children->begin;
	while (child != tree->children->end)
	{
		tmp = token_get_value((*child)->element);
		if (!tmp || !(array_push_back(args, &tmp)))
		{
			free((void *)tmp);
			array_free(args, &free);
			return (1);
		}
		++child;
	}
	ret = command_dispatch((char **)args->begin);
	array_free(args, &free);
	return (ret);
}

int		execute(t_tree *tree)
{
	return (execute_simple_command(tree));
}
