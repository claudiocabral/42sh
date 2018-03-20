/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/20 18:18:45 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>

int	process_input(char const *str)
{
	int	ret;
	int	fd = dup(STDIN_FILENO);
	ret = execute(parse(lex(str)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (ret);
}
