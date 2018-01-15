/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:30:12 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 18:09:01 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int	echo(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = !(argc > 1 && ft_strequ(argv[1], "-n"));
	if (!flag)
		++i;
	while (i < argc - 1)
		ft_printf("%s ", argv[i++]);
	ft_printf("%s%s",
			argc > 1 ? argv[i] : "",
			flag ? "\n" : "");
	return (0);
}
