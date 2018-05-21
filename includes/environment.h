/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:22:38 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 13:18:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <hash_table.h>
# include <array.h>
# include <ft_string.h>

int				ft_setenv(char const *name, char const *val, int overwrite);
char			*ft_getenv(char const *env);
char			*ft_getenv_safe(char const *env);
int				ft_prepare_env(char	**environ);
char			**get_environment(void);
t_array			*get_environment_array(void);
t_array			*copy_environment(void);
int				print_environment(t_array *env);
void			environment_remove_if(char const *data, t_predf predicate);
int				set_current_path(void);
void			set_shlvl(void);
t_string const	*set_pwd(char const *str);
t_string const	*set_oldpwd(char const *str);

#endif
