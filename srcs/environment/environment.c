/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:49:07 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 13:19:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <array.h>
#include <libft.h>
#include <ft_printf.h>
#include <environment.h>
#include <execute.h>

t_array			*copy_environment(void)
{
	t_array	*env;

	env = get_environment_array();
	return (env ? array_copy(env, 0, (t_cpyf) & ft_strdup_wrapper,
											(t_freef)free_wrapper) : 0);
}

void			environment_remove_if(char const *data, t_predf predicate)
{
	array_remove_if(get_environment_array(), &data,
					(t_freef)&free_wrapper, predicate);
}

void			print_env(char const **env, void *dummy)
{
	(void)dummy;
	ft_printf("%s\n", *env);
}

int				print_environment(t_array *env)
{
	if (env)
		array_apply(env, 0, (t_applyf) & print_env);
	return (0);
}

int				set_current_path(void)
{
	char	*path;

	if ((!(path = getcwd(0, 0))) || (ft_setenv("PWD", path, 1) == -1))
	{
		ft_dprintf(2, "21sh: error, could not set PWD to %s\n", path);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}
