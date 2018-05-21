/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/21 13:06:39 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>


static char *deglob(const char *input)
{
	return ((char*)input);
}

int	process_input(char *str)
{
	int	return_value;

	return_value = execute(parse(lex(deglob(str))));
	ft_strdel(&str);
	return (return_value);
}
