/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:06:17 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 13:58:35 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sessions.h>
#include <shellma.h>
#include <ft_printf.h>
#include <hash_table.h>
#include <environment.h>
#include <execute.h>

int	main(int argc, char **argv, char **environ)
{
	if (!ft_prepare_env(environ) || !init_path_table())
	{
		ft_dprintf(2, "minishell: failed to setup environment\n");
		return (1);
	}
	if (argc == 1)
		return (interactive_session());
	else if (ft_strequ(argv[1], "-c"))
	{
		if (argc > 2)
			return (process_input(argv[2]));
		else
		{
			ft_dprintf(2, "minishell: -c: option requires an argument\n");
			return (1);
		}
	}
	return (script_session(argc, argv));
}
