/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:06:17 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/11 14:07:18 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sessions.h>
#include <shellma.h>
#include <ft_printf.h>
#include <hash_table.h>

int	main(int argc, char **argv) {
	uint64_t	hash;

	hash = hash_string("abc");
	if (argc == 1)
		return (interactive_session());
	else if (ft_strequ(argv[1],"-c"))
	{
		if (argc > 2)
			return (process_input(argv[2]));
		else
		{
			ft_dprintf (2, "minishell: -c: option requires an argument\n");
			return (1);
		}
	}
	return (script_session(argc, argv));
}
