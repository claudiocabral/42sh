/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:42:58 by ctrouill          #+#    #+#             */
/*   Updated: 2018/02/28 14:51:22 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

int					open_history_file(void)
{
	char			*path;
	struct stat		stat;
	int				fd;

	if (!(path = getenv("HOME")))
		return (-1);
	if (!(path = ft_strjoin(path, "/.21sh_history")))
		return (-1);
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_strdel(&path);
	if (fstat(fd, &stat) == -1 || (stat.st_mode & S_IFREG) != S_IFREG)
		fd = -1;
	return (fd);
}

void				reader_to_command(char **reader, char **command)
{
	if (!*command)
		*command = ft_strdup(*reader);
	else
	{
		*command = ft_strjoinfree(*command, "\n", 'L');
		*command = ft_strjoinfree(*command, *reader, 'L');
	}
	ft_strdel(reader);
}

t_histo_list		*history_file_to_list(int fd)
{
	t_histo_list	*list;
	char			*command;
	char			*reader;
	char			*tmp;

	list = NULL;
	command = NULL;
	reader = NULL;
	while (get_next_line(fd, &reader) > 0)
	{
		if (!command || !ft_isdigit(*reader))
		{
			reader_to_command(&reader, &command);
			continue;
		}
		tmp = command;
		while (*tmp && *(tmp + 1) && *tmp >= '0' && *tmp <= '9')
			tmp++;
		history_add_command(&list, tmp + 1);
		ft_strdel(&command);
		command = ft_strdup(reader);
		ft_strdel(&reader);
	}
	ft_strdel(&command);
	return (list);
}

void				write_history(t_sh *sh, t_prompt **list,
	char *prompt_return)
{
	char	*index_history;

	if ((*list)->next && !is_only_space(prompt_return))
	{
		if (!sh->history.history ||
			ft_strcmp(prompt_return, sh->history.history->command))
		{
			history_add_command(&sh->history.history, prompt_return);
			if (sh->history.fd_history != -1)
			{
				index_history = ft_itoa(sh->history.history->index);
				write(sh->history.fd_history, index_history,
					ft_strlen(index_history));
				write(sh->history.fd_history, " ", 1);
				write(sh->history.fd_history, prompt_return,
					ft_strlen(prompt_return));
				write(sh->history.fd_history, "\n", 1);
				ft_strdel(&index_history);
			}
		}
	}
}
