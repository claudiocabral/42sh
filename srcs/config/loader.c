/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 18:44:04 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 02:53:44 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>
#include <sys/stat.h>

char			*get_path(char *path)
{
	int			size;

	if (path[0] == '~')
	{
		size = ft_strlen(path);
		ft_memmove(path, path + sizeof(char), size);
		path[size - 1] = 0;
		path = ft_strjoinfree(ft_getenv_safe("HOME"), path, 'R');
	}
	return (path);
}

char			*rc_loadable(const char *rc)
{
	struct stat	buf;

	rc = get_path((char *)rc);
	if (lstat(rc, &buf) == -1)
		return (NULL);
	if (buf.st_mode & S_IFREG)
		return ((char *)rc);
	return (NULL);
}

void			load_n_eval(const char *rc)
{
	int			fd;
	char		*line;

	line = NULL;
	if ((rc = rc_loadable(rc)))
	{
		if ((fd = open(rc, O_RDONLY)) < 0)
			return ;
		while (get_next_line(fd, &line) > 0)
			process_input(line);
		free(line);
		close(fd);
	}
}
