/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:44:19 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 13:05:20 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	builtin_unsetenv(int argc, char **argv);
int	builtin_setenv(int argc, char **argv);
int	env(int argc, char **argv);
int	cd(int argc, char **argv);
int	echo(int argc, char **argv);
int	pwd(int argc, char **argv);
int	builtin_exit(int argc, char **argv);

#endif
