/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:49:07 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/17 23:08:20 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <array.h>
#include <libft.h>
#include <ft_printf.h>
#include <environment.h>

extern char		**environ;
static t_array	*g_environ;

__attribute__((always_inline))
int				ft_strncmp_wrapper(char const **a, char const **b)
{
	return (ft_strcmp_until(*a, *b, '='));
}

void			print_env(char const **env, void *dummy)
{
	(void)dummy;
	ft_printf("%s\n", *env);
}

void	free_wrapper(void **ptr)
{
	free(*ptr);
}

__attribute__((always_inline))
void			environment_remove_if(char const* data, t_predf predicate)
{
	array_remove_if(g_environ, &data, (t_freef)&free_wrapper, predicate);
}

__attribute__((always_inline))
void			print_environment(void)
{
	array_apply(g_environ, 0, (t_applyf)&print_env);
}

int				set_current_path(void)
{
	char	*path;

	if (!(path = getcwd(0, 0)) || !ft_setenv("PWD", path, 1))
	{
		ft_dprintf(2, "minishell: error, could not set PWD\n");
		free(path);
		return (0);
	}
	free(path);
	return (1);
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
	set_current_path();
	return (1);
}

static char		*make_env(char *name, char *val)
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

char *ft_getenv(char const *env) {
  char **ptr;
  char *val;

  val = 0;
  ptr = array_find_sorted(g_environ, &env, (t_cmpf)&ft_strncmp_wrapper);
  if (ptr) {
    val = ft_strchr(*ptr, '=');
    val = val ? val + 1 : 0;
  }
  return (val);
}

int				ft_setenv(char *name, char *val, int overwrite)
{
	char	**env;
	char	*tmp;

	env = array_find_sorted(g_environ, &name, (t_cmpf)&ft_strncmp_wrapper);
	if (!overwrite && env)
		return (1);
	ZERO_IF_FAIL(tmp = make_env(name, val));
	if (env && ft_strcmp_until(tmp, name, '=') == 0)
	{
		free(*env);
		*env = tmp;
	}
	else
		array_insert_sorted(g_environ, &tmp, (t_cmpf)&ft_strncmp_wrapper);
	return (env != 0);
}
