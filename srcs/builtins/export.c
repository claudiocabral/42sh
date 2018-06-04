/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 00:45:23 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/01 04:59:36 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <builtins.h>
#include <array.h>
#include <environment.h>
#include <ft_printf.h>
#include <localvar.h>

int				export_error(char *av, t_array *env, int mode)
{
	(void)env;
	int			i;

	if (mode == 1)
	{
		i = 0;
		while (av && av[++i])
			if (av[i] != 'p')
			{
				ft_dprintf(2, "42sh: export: -%c: invalid option\n", av[i]);
				ft_dprintf(2, "Usage: export [-p] [name[=value]...]\n");
				return (-1);
			}
	}
	else if (mode == 2)
		ft_dprintf(2, "42sh: export: %s: is not an identifier\n", av);
	else if (mode == 3)
		ft_dprintf(2, "export: no such variable: %s\n", av);

	return (-1);
}


int				parse_export(int ac, char **av, t_array *env)
{
	int			ret;

	if (ac == 1)
		array_apply(env, 0, (t_applyf) & print_export_env);
	else
	{
		if ((ret = identify_opt(av, env, 1)) > 1)
		{
			print_export(av, env, ret);
			return (0);
		}
		return (ret >= 0 ? ret : -1);
	}
	return (0);
}

int				export_withequal(char *av, int ret)
{
	char		*tmp;
	char		*tmp1;
	char		**var;

	ZERO_IF_FAIL(tmp = ft_strsub(av, 0, ret));
	if (is_valid_var(av) == -1)
		return (export_error(av, NULL, 2));
	var = array_find(get_environment_array(), &tmp, (t_cmpf) &
			ft_strncmp_wrapperb);
	remove_quotes_var(&av[ret + 1]);
	if (var)
	{
		free(*var);
		*var = ft_strdup(av);
	}
	else
	{
		tmp1 = ft_strdup(av);
		array_push_back(get_environment_array(), &tmp1);
	}
	tmp ? free(tmp) : 0;
	return (1);
}

int				export_withoutequal(char *av)
{
	char		**var;
	char		*tmp;

	if (is_valid_var(av) == -1)
		return (export_error(av, NULL, 2));
	var = array_find(get_localvar_array(), &av, (t_cmpf) &
		ft_strncmp_wrapperb);
	tmp = var ? ft_strdup(*var) : NULL;
	if (tmp)
	{
		array_push_back(get_environment_array(), &tmp);
		free(*var);
	}
	else
	{
		tmp = ft_strdup(av);
		array_push_back(get_environment_array(), &tmp);
	}
	return (1);;
}

int				builtin_export(int ac, char **av)
{
	t_array		*env;
	int			i;
	int			ret;

	i = 0;
	if (!(env = copy_environment()))
	{
		ft_dprintf(2, "42sh: export: failed copy_environment()\n");
		return (-1);
	}
	if ((i = parse_export(ac, av, env) > 0))
		while (av[i])
		{
			if ((ret = ft_strchri(av[i], '=')) != -1)
				export_withequal(av[i++], ret);
			else
				export_withoutequal(av[i++]);
		}
	env ? array_free(env, (t_freef) & free_wrapper) : 0;
	return (1);
}
