/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:04:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/17 15:14:45 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <builtins.h>
#include <ft_printf.h>

int	builtin_setenv(int argc, char **argv)
{
	char	*name;

	if (argc > 3)
	{
		ft_dprintf(2, "setenv: Too many arguments.\n");
		return (1);
	}
	if (argc == 1)
	{
		print_environment();
		return (0);
	}
	if (argc == 2)
		name = "";
	else
		name = argv[2];
	ft_setenv(argv[1], name, 1);
	return (0);
}
