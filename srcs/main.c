/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:06:17 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 19:21:00 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sessions.h>
#include <shellma.h>
#include <ft_printf.h>

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (interactive_session());
	else if (ft_strequ(argv[1],"-c"))
	{
		if (argc > 2)
			return (execute(parse(lex(argv[2]))));
		else
		{
			ft_dprintf (2, "minishell: -c: option requires an argument\n");
			return (1);
		}
	}
	return (script_session(argc, argv));
}
