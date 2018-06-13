/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:23:10 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/13 11:06:39 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <ft_string.h>
# include <hash_table.h>
# include <array.h>
# include <tree.h>
# include <token.h>

typedef int		(*t_exec)(int argc, char **argv);

typedef struct	s_fd_pair
{
	int	from;
	int	to;
}				t_fd_pair;

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
int				remove_quotes(char *str);
int				init_builtins(void);
int				generate_paths(void);
int				init_path_table(void);
void			free_global_paths(void);
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
int				branch_equals(t_tree *tree, t_tag type);
int				command_dispatch(char **argv, char **env, char const *who);
int				execute_commands(t_tree *tree);
int				execute_simple_command(t_tree *tree);
int				execute_pipe(t_tree	*tree);
int				collect_args(t_tree **begin, t_tree **end,
								t_array *args, t_array *fds);
t_fd_pair		redirect(t_tree *tree);
t_fd_pair		deal_with_aggregator(t_fd_pair fd);
int				check_agreggator(t_token *token);
void			swap_fd(t_fd_pair *fd);
void			execute_cleanup(t_array *fds, t_array *args,
													t_array *args_copy);
int				is_localvar(char *tmp);
int				special_char(char c);
char			get_special_char(char c);
void			remove_bquote(char *str);
char			*ft_strchr_skipbs(char const *s, int c);

#endif
