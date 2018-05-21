/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:12:53 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 12:03:53 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <libft.h>
#include <sys/types.h>

#include <globbing.h>
#include "internals.h"

/*
** Internal wrapper
** of the globbing system
** Return the glob pattern
** expansion
*/

static char		*deflate(const char *origin, char *result, int state)
{
	t_glob glob;

	if ((state = compute_globbing(origin, &glob)) > 0)
		if ((result = build_result(glob.final_list, NULL, 0, NULL)) != NULL)
			return (result);
	return (NULL);
}

/*
** Return function wrapper
** for the runner middleware.
*/

char			*deglob(const char *input, char *token, char *blob)
{
	char		deglobed[4096];

	token = strtok((char*)input, " \t\n");
	while (token != NULL)
	{
		if (needs_globbing(token, 0))
		{
			if ((blob = deflate(token, NULL, 0x0)) == NULL)
			{
				printf("Unmatched globs\n");
				exit(EXIT_FAILURE);
			}
			strcat(deglobed, blob);
			strcat(deglobed, " ");
			free(blob);
		}
		else
		{
			strcat(deglobed, token);
			strcat(deglobed, " ");
		}
		token = strtok(NULL, " \t\n");
	}
	return ((deglobed[0] == '\0') ? NULL
			: strdup(deglobed));
}
