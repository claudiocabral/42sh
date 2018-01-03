/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:22:38 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/03 09:48:44 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <hash_table.h>
# include <array.h>

int				ft_setenv(char const *name, char const *val, int overwrite);
char			*ft_getenv(char const *env);
int				ft_prepare_env(void);
char			**get_environment(void);
t_array			*copy_environment(void);
void			print_environment(void);
void			environment_remove_if(char const* data, t_predf predicate);

#endif
