/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:50:24 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/10 10:40:16 by claudioca        ###   ########.fr       */
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

void	execute_simple_command(t_tree *tree)
{
	t_array		*args;
	t_tree		**child;
	char		*tmp;

	args = array_create(sizeof(char *), 16);
	child = (t_tree **)tree->children->begin;
	tmp = token_get_value((*child)->element);
	array_push_back(args, &tmp);
	++child;
	while (child != tree->children->end)
	{
		tmp = token_get_value((*child)->element);
		array_push_back(args, &tmp);
		++child;
	}
	invoke(((char const **)args->begin)[0], (char **)args->begin);
}

int		execute(t_tree *tree)
{
	execute_simple_command(tree);
	return (0);
}
