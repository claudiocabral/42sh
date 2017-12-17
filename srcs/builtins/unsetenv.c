/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:32:37 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/17 16:28:59 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

int	glob_match(char const *s1, char const *s2)
{
	if ((*s1 == '\0' || *s1 == '=') && *s2 == '\0')
		return (1);
	else if (*s1 == '\0' || *s1 == '=' || *s2 == '\0')
		return (0);
	else if (*s1 == *s2)
		return (glob_match(s1 + 1, s2 + 1));
	else if (*s2 == '*')
		return (glob_match(s1 + 1, s2) || glob_match(s1 + 1, s2 + 1));
	else
		return (0);
}

__attribute__((always_inline))
int	glob_match_wrapper(char const **s1, char const *s2)
{
	return (glob_match(*s1, s2));
}

int	builtin_unsetenv(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		environment_remove_if(argv[i], (t_predf)&glob_match_wrapper);
		++i;
	}
	return (0);
}
