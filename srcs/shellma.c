/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/21 18:07:25 by ctrouill         ###   ########.fr       */
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

	if ((input = deglob(str, NULL, NULL)) == NULL)
		return (ft_printf("42sh: Invalid Pattern OR not matchs found.\n"));
	return_value = execute(parse(lex(input)));
	ft_strdel(&str);
	free(input);
	return (return_value);
}
