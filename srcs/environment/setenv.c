/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:18:10 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/15 14:59:27 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <execute.h>

static char		*make_env(char const *name, char const *val)
{
	size_t	size;
	char	*env;

	size = ft_strlen(name) + ft_strlen(val) + 2;
	ZERO_IF_FAIL(env = (char *)malloc(size));
	env[0] = 0;
	ft_strcat(env, name);
	ft_strcat(env, "=");
	ft_strcat(env, val);
	return (env);
}

int				ft_setenv(char const *name, char const *val, int overwrite)
{
	char	**env;
	char	*tmp;

	env = array_find(get_environment_array(), &name,
								(t_cmpf) & ft_strncmp_wrapper);
	if (!overwrite && env)
		return (1);
	ZERO_IF_FAIL(tmp = make_env(name, val));
	if (env && (ft_strcmp_until(name, *env, '=') == 0))
	{
		free(*env);
		*env = tmp;
	}
	else
		env = array_push_back(get_environment_array(), &tmp);
	if (ft_strequ(name, "PATH"))
		generate_paths();
	return (env != 0 ? 0 : -1);
}
