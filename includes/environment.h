/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:22:38 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/14 14:12:11 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <hash_table.h>

typedef struct	s_binary_path
{
	char const		*path;
	t_hash_table	binaries;
}				t_binary_path;

int				ft_setenv(char *name, char *val, int overwrite);
char			*ft_getenv(char const *env);
int				ft_prepare_env(void);
char			**get_environment(void);

#endif
