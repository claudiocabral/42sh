/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:44:19 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 17:14:55 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <ft_string.h>
# include <array.h>

int				builtin_unsetenv(int argc, char **argv);
int				builtin_setenv(int argc, char **argv);
int				env(int argc, char **argv);
int				cd(int argc, char **argv);
int				echo(int argc, char **argv);
int				pwd(int argc, char **argv);
int				builtin_exit(int argc, char **argv);
t_string const	*set_pwd(char const *str);
t_string const	*set_oldpwd(char const *str);
t_string		*clean_path(char *path);
int				builtin_export(int ac, char **av);
int				export_error(char *av, t_array *env, int mode);
int				ft_strncmp_wrapperb(char const **a, char const **b);
int				identify_opt(char **av, t_array *env, int mode);
void			print_export_all(char const **env, void *dummy);
void			print_export_env(char const **env, void *dummy);
int				print_export(char **av, t_array *env, int i);
int				builtin_unset(int argc, char **argv);
int				builtin_alias(int argc, char **argv);
int				builtin_unalias(int argc, char **argv);
int				ft_prepare_alias(void);
char			*ft_getalias(char const *var);
t_array			*get_alias_array(void);
int				init_alias(void);
void			print_alias_all(char const **alias, void *dummy);
int				print_alias(char **av, t_array *alias, int i);
int				alias_error(char *av, char opt, int mode);
char			*alias_replace(char *av);
int				get_alias_to_replace(t_string *str, int *i);
int				is_valid_alias(char *alias);
char			*alias_replace_process(char *av);
int				help(int argc, char **argv);
int				loop_alias_replace(char **tmp, char **tmp2, char **tmp1);
#endif
