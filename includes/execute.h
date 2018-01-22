/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:23:10 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 19:27:40 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <ft_string.h>
# include <hash_table.h>
# include <array.h>
# include <tree.h>

typedef int		(*t_exec)(int argc, char **argv);

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

char			*expand(char *value);
void			remove_backslash(char *str);
void			remove_quotes(char *str);
int				init_builtins(void);
int				generate_paths(void);
int				init_path_table(void);
int				init_paths(t_array **paths);
t_binary_path	*make_path_entry(char const *name, size_t size);
t_string		*binary_path_set_buffer(t_binary_path *path,
											char const *suffix);
int				fill_table(t_binary_path *path);
int				invoke_builtin(t_builtin const *command, char **args);
int				invoke(char const *process, char **args, char **env,
															char const *who);
int				wait_process(pid_t pid);
char const		*command_name_lookup(char const *name);
t_builtin		*get_builtin_command(char const *name);
int				dispatch_branch(t_tree *tree);
int				command_dispatch(char **argv, char **env, char const *who);
int				execute_commands(t_tree *tree);
int				execute_simple_command(t_tree *tree);
int				execute_pipe(t_tree	*tree);

#endif
