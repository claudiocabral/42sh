/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 11:26:38 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/17 14:46:44 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <builtins.h>
#include <ft_printf.h>

int	pwd(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		ft_dprintf(2, "pwd: too many arguments\n");
	ft_printf("%s\n", ft_getenv_safe("PWD"));
	return (0);
}
