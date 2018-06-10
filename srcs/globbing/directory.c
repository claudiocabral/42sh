/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:58:42 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/10 11:25:44 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

#include "internals.h"

/*
** Pattern checker that
** alter buffer instead
** bool return
** @return nil
*/

static void		verify_pattern(char **name, char *tmp, int i)
{
	tmp = *name;
	while (tmp[i] && tmp[i] != '*' &&
		tmp[i] != '[' && tmp[i] != '?')
	{
		if (tmp[i] == '/')
			*name = &tmp[i + 1];
		i++;
	}
}

/*
** Walker body for the glory of the norm
** @return nil
*/

static void		walker_body(t_helper *h, struct dirent *entry,
							char **pattern, t_list **matches)
{
	h->filename = ft_strjoin(h->cur_path, entry->d_name);
	h->file_bak = h->filename;
	if (pattern_dispatcher(h, entry->d_name, *pattern, matches))
	{
		ft_memset(h->filename, 0x20, MAGIC_OFFSET);
		store_result(matches, h->filename, NULL, NULL);
	}
	else
		free(h->filename);
}

/*
** Dirwalker that find and store matches
** into an linked list and fill the globbing
** info structure. The temporary match list
** will be added in prepend to the final return.
** While reading in directory, we keep the `local`
** directory/file to avoid multi redundant recursions.
** @return Boolean/Success
*/

t_bool			call_dirwalker(t_helper h, char *pattern,
					t_list **results, t_list *matches)
{
	DIR				*mydir;
	struct dirent	*entry;

	h.cur_path = retrieve_valid_path(h.file_bak, pattern, 0, 0);
	verify_pattern(&pattern, NULL, 0);
	if ((mydir = opendir(h.cur_path)) != NULL)
	{
		while ((entry = readdir(mydir)))
			walker_body(&h, entry, &pattern, &matches);
		closedir(mydir);
	}
	free(h.cur_path);
	ft_lstprepend(results, matches);
	return (FALSE);
}
