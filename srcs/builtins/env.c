/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:41:11 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 13:21:04 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <builtins.h>
#include <array.h>
#include <environment.h>
#include <execute.h>
#include <ft_printf.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int	safe_push_back(t_array *local_env, char *data)
{
	char	*tmp;

	if (!(tmp = ft_strdup(data)))
	{
		array_free(local_env, (t_freef) & free_wrapper);
		return (0);
	}
	if (!array_push_back(local_env, &tmp))
	{
		free(tmp);
		array_free(local_env, (t_freef) & free_wrapper);
		return (0);
	}
	return (1);
}

int			do_env(int argc, char **argv, t_array *local_env)
{
	int			i;
	int			ret;
	char const	*command;

	i = 0;
	while (i < argc && ft_strchr(argv[i], '='))
	{
		if (!safe_push_back(local_env, argv[i]))
			return (1);
		++i;
	}
	if (i == argc)
		ret = print_environment(local_env);
	else
		ret = invoke(command, argv + i, local_env->begin, "env");
	array_free(local_env, (t_freef) & free_wrapper);
	return (ret);
}

int			env_parser(int *argc, char ***argv)
{
	int	i;
	int	j;
	int	ret;

	ret = ft_strncmp((*argv)[1], "-i", 2) == 0 ? 1 : 0;
	i = 0;
	while (++i < *argc && (*argv)[i][0] == '-')
	{
		j = 0;
		while ((*argv)[i][++j])
		{
			if (ft_strequ((*argv)[i], "--"))
				break ;
			if ((*argv)[i][j] != 'i')
			{
				ft_dprintf(2, "env: illegal option -- %c\n", (*argv)[i][j]);
				return (-1);
			}
		}
	}
	*argc -= i;
	*argv += i;
	return (ret);
}

int			env(int argc, char **argv)
{
	int		flag_i;
	t_array	*local_env;

	if (argc == 1)
	{
		print_environment(get_environment_array());
		return (0);
	}
	if ((flag_i = env_parser(&argc, &argv)) == -1)
		return (1);
	else if (flag_i == 0)
		local_env = copy_environment();
	else
		local_env = array_create(sizeof(char *), 16);
	if (!local_env)
	{
		ft_dprintf(2, "env: failed to create new environment\n");
		return (1);
	}
	return (do_env(argc, argv, local_env));
}
