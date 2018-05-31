/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:05:53 by ccabral           #+#    #+#             */
/*   Updated: 2018/05/31 03:27:12 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <array.h>
#include <localvar.h>
#include <builtins.h>

static t_array	*g_environ = 0;

int				ft_prepare_env(char **environ)
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
			array_free(array, (t_freef) & free_wrapper);
			return (0);
		}
		if ((!array_push_back(array, &tmp)))
			return (0);
		++i;
	}
	g_environ = array;
	if (!ft_getenv("PATH"))
		ft_setenv("PATH", "/usr/bin:/bin", 0);
	ft_prepare_localvar();
	set_shlvl();
	set_current_path();
	return (1);
}

t_array			*get_environment_array(void)
{
	return (g_environ);
}

char			**get_environment(void)
{
	return (g_environ ? g_environ->begin : 0);
}

char			*ft_getenv(char const *env)
{
	char **ptr;
	char *val;

	val = 0;
	ptr = array_find(g_environ, &env, (t_cmpf) & ft_strncmp_wrapperb);
	if (ptr)
	{
		val = ft_strchr(*ptr, '=');
		val = val ? val + 1 : 0;
	}
	return (val);
}

char			*ft_getenv_safe(char const *env)
{
	char *val;

	if (!(val = ft_getenv(env)))
		return ("");
	return (val);
}
