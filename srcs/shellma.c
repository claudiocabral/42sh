/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/09 02:19:50 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>
#include <globbing.h>
#include <ft_printf.h>
#include <stdio.h>


#include "libft.h"

/*
 ** Centralized executor
 ** @return program status
 */

int			process_input_after_backtick(char *str)
{
	int		return_value;
	char	*input;

	str = alias_replace(str);
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

/*
** process_backtits("echo `echo salut`")
** return "echo salut"
*/

char		*ft_strreplace(char *origin, char *piece, size_t pos, size_t len)
{
	char *debut;
	char *millieu;
	char *fin;
	char *total;

	debut = ft_memdup(origin, pos);
//	ft_printf("Début : '%s'\n", debut);
	millieu = piece;
//	ft_printf("Millieu : '%s'\n", millieu);
	fin = ft_strdup(origin + len + 1);
//	ft_printf("Fin : '%s'\n", fin + 1);
	total = ft_vjoin(3, debut, millieu, fin);
	free(debut);
	free(fin);
	return (total);
}


void		dellines(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}

char 		*backtits_replace(char *str, size_t pos)
{
	char 	*start;
	char	*stop;
	char	*exec;
	int		p[2];
	int		out;
	char    print[1024];
	char	*now;


	start = ft_strchr(str + pos, '`');
	if (!start)
		return (str);
	if(!(stop = ft_strchr(start + 1, '`')))
		return (str); // Error !

	exec = ft_memdup(start + 1, stop - start - 1);
		out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	close(p[1]);
	process_input_after_backtick(exec);
	close(1);

	print[read(p[0], print, 1023)] = '\0';

	dup2(out, 1);
	close(p[0]);
	close(out);

	dellines((char*)print);
	
	
	now = (ft_strreplace(str, (char*) print, start - str, stop - str));
	free(str);
	now = (backtits_replace(now, (start - str) + ft_strlen(print)));
	
	return (now);
}




int			process_input(char *str)
{
	return process_input_after_backtick(backtits_replace(str, 0));
}
