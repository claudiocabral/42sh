/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:12:53 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/28 10:31:04 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>
#include <libft.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

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
	{
		if ((result = build_result(glob.final_list, NULL, 0, NULL)) != NULL)
		{
			return (result);
		}
	}
	return (NULL);
}

/*
** Return function wrapper
** for the runner middleware.
*/

char			*deglob(const char *input, char *token, char *blob)
{
	char		*deglobed = NULL;
	char		*tmp = NULL;

	deglobed = malloc(1);
	ft_bzero(deglobed, ft_strlen(deglobed));
	token = ft_strtok((char*)input, " \t\n");
	while (token != NULL)
	{
		if (needs_globbing(token, 0))
		{
			if ((blob = deflate(token, NULL, 0)) == NULL)
			{
				free(deglobed);
				return (NULL);
			}
			tmp = ft_vjoin(3, deglobed, blob, " ");
			deglobed = ft_strdup(tmp);
			free(tmp);
			free(blob);
		}
		else
		{
			tmp = ft_vjoin(3, deglobed, token, " ");
			deglobed = ft_strdup(tmp);
			free(tmp);
		}
		token = ft_strtok(NULL, " \t\n");
	}
	return (deglobed);
}
