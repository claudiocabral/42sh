/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:44:19 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/21 18:21:21 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <ft_string.h>

int			builtin_unsetenv(int argc, char **argv);
int			builtin_setenv(int argc, char **argv);
int			env(int argc, char **argv);
int			cd(int argc, char **argv);
int			echo(int argc, char **argv);
int			pwd(int argc, char **argv);
int			builtin_exit(int argc, char **argv);
t_string	*set_pwd(char *str);
t_string	*clean_path(char *path);

#endif
