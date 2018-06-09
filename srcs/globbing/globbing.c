/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:12:53 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/09 18:26:59 by ctrouill         ###   ########.fr       */
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
#include <lexer.h>

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
		dot_reduce(&glob.final_list, origin, NULL);
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

char			*deglob(const char *input, char *token, char *blob,
					char *deglobed, char *tmp)
{
	char		ending[2];

	deglobed = malloc(1);
	ft_bzero(deglobed, 1);
	get_quote(0);
	token = strtok_glob((char*)input, " \t\n", ending);
	while (token != NULL)
	{
		if (needs_globbing(token, 0))
		{
			if ((blob = deflate(token, NULL, 0)) == NULL)
			{
				free(deglobed);
				return (NULL);
			}
			if ((tmp = ft_vjoin(3, deglobed, blob, ending)) == NULL)
				return (NULL);
			free(deglobed);
			deglobed = ft_strdup(tmp);
			free(tmp);
			free(blob);
		}
		else
		{
			if ((tmp = ft_vjoin(3, deglobed, token, ending)) == NULL)
				return (NULL);
			free(deglobed);
			deglobed = ft_strdup(tmp);
			free(tmp);
		}
		token = strtok_glob(NULL, " \t\n", ending);
	}
	return (deglobed);
}
