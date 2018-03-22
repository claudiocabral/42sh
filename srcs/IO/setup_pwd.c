/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:13:14 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 14:14:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <builtins.h>
#include <io.h>

int				set_initial_path(void)
{
	char	*tmp;

	ZERO_IF_FAIL(tmp = getcwd(0, 0));
	set_pwd(tmp);
	free(tmp);
	return (1);
}
