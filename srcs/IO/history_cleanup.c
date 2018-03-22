/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:54:15 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 17:25:03 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <io.h>
#include <environment.h>
#include <libft.h>

void	history_cleanup(t_terminal *terminal, int save)
{
	terminal->buffer_size = 16;
	close(terminal->history_fd);
	dup2(save, STDIN_FILENO);
	close(save);
	terminal->history_fd = 0;
	terminal->fd = STDIN_FILENO;
}

char	*get_history_path(void)
{
	char	*path;
	char	*tmp_path;

	if (!(tmp_path = ft_getenv("HOME")))
		return (0);
	if (!(path = (char *)malloc(sizeof(char)
					* (ft_strlen(tmp_path)
					+ ft_strlen("/.21_history") + 1))))
		return (0);
	*path = 0;
	ft_strcat(path, tmp_path);
	ft_strcat(path, "/.21_history");
	return (path);
}
