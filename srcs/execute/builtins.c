/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:40:55 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/15 13:01:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <execute.h>
#include <builtins.h>

static t_hash_table		*g_builtins;

static uint64_t			builtin_hash(t_builtin *builtin)
{
	return (hash_string(&builtin->name));
}

int						builtin_compare(t_builtin *a, t_builtin *b)
{
	return (ft_strcmp(a->name, b->name));
}

static void				add_builtin(char *name, t_exec func)
{
	t_builtin	builtin;

	builtin.name = name;
	builtin.func = func;
	hash_table_insert(g_builtins, &builtin);
}

int						init_builtins(void)
{
	ZERO_IF_FAIL(g_builtins = hash_table_create(sizeof(t_builtin), 16,
					(t_hashf) & builtin_hash, (t_cmpf) & builtin_compare));
	add_builtin("exit", &builtin_exit);
	add_builtin("cd", &cd);
	add_builtin("echo", &echo);
	add_builtin("pwd", &pwd);
	add_builtin("env", &env);
	add_builtin("setenv", &builtin_setenv);
	add_builtin("unsetenv", &builtin_unsetenv);
	return (1);
}

t_builtin				*get_builtin_command(char const *name)
{
	t_builtin	dummy;

	dummy.name = name;
	return (hash_table_find(g_builtins, &dummy));
}
