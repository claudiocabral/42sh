/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:44:19 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/31 02:40:41 by gfloure          ###   ########.fr       */
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
int				identify_opt(char **av, t_array *env);
void			print_export_all(char const **env);
void			print_export_env(char const **env);
int				print_export(char **av, t_array *env, int i);
int				builtin_unset(int argc, char **argv);

#endif
