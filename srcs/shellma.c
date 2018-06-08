/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/08 22:32:31 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>
#include <globbing.h>
#include <ft_printf.h>

/*
** Centralized executor
** @return program status
*/

int			process_input(char *str)
{
	int		return_value;
	char	*input;

	if ((input = deglob(str, NULL, NULL, NULL, NULL)) == NULL)
	{
		free(str);
		return (ft_printf("42sh: No matchs found.\n"));
	}
	input = alias_replace((char *)input);
	return_value = execute(parse(lex(input)));
	str ? ft_strdel(&str) : 0;
	input ? free(input) : 0;
	return (return_value);
}
