/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:12:53 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 16:59:18 by ctrouill         ###   ########.fr       */
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
		printf("In the state scope\n");
		if ((result = build_result(glob.final_list, NULL, 0, NULL)) != NULL)
		{
			printf("In the result scope\n");
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
	char		deglobed[409];

	token = ft_strtok((char*)input, " \t\n");
	while (token != NULL)
	{
		if (needs_globbing(token, 0))
		{
			if ((blob = deflate(token, NULL, 0)) == NULL)
				return (NULL);
			ft_strcat(deglobed, blob);
			ft_strcat(deglobed, " ");
			free(blob);
		}
		else
		{
			ft_strcat(deglobed, token);
			ft_strcat(deglobed, " ");
		}
		printf("debug: %s\n", deglobed);
		token = ft_strtok(NULL, " \t\n");
	}
	return ((deglobed[0] == '\0') ? NULL
			: strdup(deglobed));
}
