/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:43:44 by gfloure           #+#    #+#             */
/*   Updated: 2018/05/31 04:34:08 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <ft_printf.h>
#include <environment.h>
#include <libft.h>

void			print_export_all(char const **env)
{
	int			ret;
	const char		*str;

	str = *env;
	ret = ft_strchri(str, '=');
	ft_printf("export %s", str);
	ret == -1 ? ft_printf("=\'\'\n") : ft_printf("\n");
}

void			print_export_env(char const **env)
{
	int			ret;
	const char		*str;

	str = *env;
	ret = ft_strchri(str, '=');
	ft_printf("%s", str);
	ret == -1 ? ft_printf("=\'\'\n") : ft_printf("\n");
}

int				print_export(char **av, t_array *env, int i)
{
	const char	**str;
	t_array		*array;

	if ((av && !av[i]) || !av)
	{
		if (env)
			array_apply(env, 0, (t_applyf) & print_export_all);
		return (1);
	}
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	while (av && av[i])
	{
		if ((str = array_find(get_environment_array(), &av[i], \
						(t_cmpf) & ft_strncmp_wrapperb)))
			array_push_back(array, str);
		else
			export_error(av[i], env, 3);
		str = NULL;
		i++;
	}
	array_apply(array, 0, (t_applyf) & print_export_env);
	array_free(array, &noop);
	return (1);
}
