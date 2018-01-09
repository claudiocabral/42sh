/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:23:10 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/09 17:56:28 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <ft_string.h>
# include <hash_table.h>
# include <array.h>
# include <tree.h>

typedef int	(*t_exec)(int argc, char **argv);

typedef struct	s_builtin
{
	char const	*name;
	t_exec		func;
}				t_builtin;

typedef struct	s_binary_path
{
	char			*name;
	t_string		*buffer;
	t_hash_table	*table;
}				t_binary_path;

int			init_path_table(void);
int			init_paths(t_array **paths);
t_string	*binary_path_set_buffer(t_binary_path *path, char const *suffix);
int			invoke_builtin(t_builtin const *command, char **args);
int			invoke(char const *process, char **args);
int			wait_process(pid_t pid);
char const	*command_name_lookup(char const *name);
t_builtin	*get_builtin_command(char const *name);
int			command_dispatch(char **argv);
int			execute_simple_command(t_tree *tree);
int			execute_pipe(t_tree	*tree);

#endif
