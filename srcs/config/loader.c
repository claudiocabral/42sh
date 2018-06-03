/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 18:44:04 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/03 19:04:58 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>
#include <sys/stat.h>

t_bool			rc_loadable(const char *rc)
{
	struct stat	buf;

	if (lstat(rc, &buf) == -1)
		return (FALSE);
	if (buf.st_mode & S_IFREG)
		return (TRUE);
	return (FALSE);
}

void			load_n_eval(const char *rc)
{
	int			fd;
	char		*line;

	line = NULL;
	if ((fd = open(rc, O_RDONLY)) < 0)
		return ;
	while (get_next_line(fd, &line) > 0)
		process_input(line);
	free(line);
	close(fd);
}
