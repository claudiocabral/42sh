/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:49:07 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 11:47:40 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <array.h>

extern char		**environ;
static t_array	*g_environ;

__attribute__((always_inline))
int				ft_strncmp_wrapper(char const *a, char const *b)
{
	return (ft_strncmp(a, b, ft_strlen(a)));
}

char			*ft_getenv(char const *env)
{
	char	*val;
	val = array_find_sorted(g_environ, env, (t_cmpf)&ft_strncmp_wrapper);
	if (val)
	{
		val = ft_strchr(val, '=');
		val = val ? val + 1 : 0;
	}
	return (val);
}

__attribute__((always_inline))
char			**get_environment(void)
{
	return (g_environ ? g_environ->begin : 0);
}

int				ft_prepare_env(void)
{
	t_array	*array;
	char	*tmp;
	int		i;

	ZERO_IF_FAIL(array = array_create(sizeof(char *), 32));
	i = 0;
	while (environ[i])
	{
		if (!(tmp = ft_strdup(environ[i])))
		{
			array_free(array, &free);
			return (0);
		}
		if ((!array_push_back(array, &tmp)))
			return (0);
		++i;
	}
	g_environ = array;
	return (1);
}

static char		*make_env(char *name, char *val)
{
	size_t	size;
	char	*env;

	size = ft_strlen(env) + ft_strlen(val) + 2;
	ZERO_IF_FAIL(env = (char *)malloc(size));
	env[0] = 0;
	ft_strcat(env, name);
	ft_strcat(env, "=");
	ft_strcat(env, val);
	return (env);
}

int				ft_setenv(char *name, char *val, int overwrite)
{
	char	*env;
	char	*tmp;

	env = array_find_sorted(g_environ, name, (t_cmpf)&ft_strncmp_wrapper);
	if (!overwrite && env)
		return (1);
	ZERO_IF_FAIL(tmp = make_env(name, val));
	free(env);
	if (env)
		env = tmp;
	else
		array_insert_sorted(g_environ, &tmp, (t_cmpf)&ft_strncmp_wrapper);
	return (env != 0);
}
