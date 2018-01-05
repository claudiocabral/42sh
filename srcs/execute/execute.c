/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:50:24 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 16:39:41 by claudioca        ###   ########.fr       */
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

char	*expand(char *value)
{
	size_t	size;
	char	*str;

	size = 0;
	str = value;
	if (ft_strncmp(value, "~/", 2) == 0)
	{
		size = ft_strlen(ft_getenv("HOME")) + ft_strlen(value);
		if (!(str = (char *)malloc(sizeof(char) * size)))
		{
			free(value);
			return (0);
		}
		str[0] = 0;
		ft_strcat(str, ft_getenv("HOME"));
		ft_strcat(str, "/");
		ft_strcat(str, value + 2);
		free(value);
	}
	else if (ft_strcmp(value, "~") == 0)
	{
		free(value);
		str = ft_strdup(ft_getenv("HOME"));
	}
	return (str);
}

int		execute_simple_command(t_tree *tree)
{
	t_array		*args;
	t_tree		**child;
	void		*tmp;
	int			ret;

	if (!(args = array_create(sizeof(char *), 16)))
		return (1);
	child = (t_tree **)tree->children->begin;
	while (child != tree->children->end)
	{
		tmp = token_get_value((*child)->element);
		tmp = expand(tmp);
		if (!tmp || !(array_push_back(args, &tmp)))
		{
			free(tmp);
			array_free(args, (t_freef)&free_wrapper);
			return (1);
		}
		++child;
	}
	ret = command_dispatch((char **)args->begin);
	tree_free(tree, (t_freef)&noop);
	array_free(args, (t_freef)&free_wrapper);
	return (ret);
}

int		execute(t_tree *tree)
{
	if (tree)
		return (execute_simple_command(tree));
	return (0);
}
