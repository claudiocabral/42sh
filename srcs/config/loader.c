/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 18:44:04 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/10 18:07:49 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>
#include <sys/stat.h>

char			*get_path(char const *path)
{
	char		*str;

	str = 0;
	if (path[0] == '~')
	{
		str = ft_vjoin(2, ft_getenv_safe("HOME"), path + 1);
	}
	return (str ? str : ft_strdup(path));
}

int				rc_loadable(const char *rc)
{
	struct stat	buf;

	if (!rc)
		return (0);
	if (lstat(rc, &buf) == -1)
		return (0);
	if (buf.st_mode & S_IFREG)
		return (1);
	return (0);
}

void			load_n_eval(const char *rc)
{
	int			fd;
	char		*line;
	char		*path;

	line = NULL;
	path = get_path(rc);
	if (rc_loadable(path))
	{
		if ((fd = open(rc, O_RDONLY)) < 0)
		{
			free(path);
			return ;
		}
		while (get_next_line(fd, &line) > 0)
			process_input(line);
		free(line);
		close(fd);
	}
	free(path);
}
