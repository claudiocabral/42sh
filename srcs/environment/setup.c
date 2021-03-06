/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:10:49 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 14:10:52 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <environment.h>

void	set_shlvl(void)
{
	char	*level;
	int		value;
	char	*str;

	level = ft_getenv_safe("SHLVL");
	value = ft_atoi(level);
	if (!(str = ft_itoa(value + 1)))
		return ;
	ft_setenv("SHLVL", str, 1);
	free(str);
}
