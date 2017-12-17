/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:22:38 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/17 16:20:49 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <hash_table.h>

int				ft_setenv(char *name, char *val, int overwrite);
char			*ft_getenv(char const *env);
int				ft_prepare_env(void);
char			**get_environment(void);
void			print_environment(void);
void			environment_remove_if(char const* data, t_predf predicate);

#endif
