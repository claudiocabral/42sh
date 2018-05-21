/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnesia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:01:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 11:03:41 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#include "internals.h"

void		store_result(t_list **lst, char *s,
				t_list *tmp, t_list *add)
{
	t_list		*last;

	last = NULL;
	tmp = *lst;
	if (tmp != NULL)
	{
		while (tmp && !(offsetcmp(s, tmp->content, NULL, NULL) <= 0))
		{
			last = tmp;
			tmp = tmp->next;
		}
		add = ft_xlstnew(s, ft_strlen(s) + 1);
		add->next = tmp;
		if (last != NULL)
			last->next = add;
		else
			*lst = add;
	}
	else
		*lst = ft_xlstnew(s, ft_strlen(s) + 1);
}

char		*create_fullpath(char *local, char *name,
					int j, char *path)
{
	char		*fullpath;

	path = ft_strnew(j + 1);
	ft_strncpy(path, name, j);
	ft_strncat(path, "/", 1);
	fullpath = ft_strjoin(local, path);
	free(path);
	return (fullpath);
}

char		*retrieve_valid_path(char *local, char *name,
					int i, int j)
{
	char		*fullpath;

	while (name[i] && name[i] != '*'
		&& name[i] != '[' && name[i] != '?')
	{
		if (name[i] == '/')
			j = i;
		i++;
	}
	if (local == NULL)
	{
		if (i == 0)
		{
			name = ".";
			j = 1;
		}
		fullpath = ft_strnew(j + 1);
		ft_strncpy(fullpath, name, j);
		ft_strcat(fullpath, "/");
	}
	else
		return (create_fullpath(local, name, j, NULL));
	return (fullpath);
}
