/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:06:17 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/13 11:51:38 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash_table.h>
#include <mysh.h>
#include <loader.h>

int			main(int argc, char **argv, char **environ)
{
	(void)argv;
	if (!isatty(STDIN_FILENO))
		return (1);
	if (!ft_prepare_env(environ) || !init_path_table())
	{
		ft_dprintf(2, "42sh: failed to setup environment\n");
		return (1);
	}
	load_n_eval(ft_strdup(SH_RC));
	if (argc == 1)
		return (interactive_session());
	return (0);
}
