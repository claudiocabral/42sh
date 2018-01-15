/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:32:37 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 16:34:14 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <execute.h>

int	glob_match(char const *s1, char const *s2)
{
	if ((*s1 == '\0' || *s1 == '=') && *s2 == '\0')
		return (1);
	else if (*s1 == '\0' || *s2 == '\0')
		return (0);
	else if (*s1 == *s2)
		return (glob_match(s1 + 1, s2 + 1));
	else if (*s2 == '*')
		return (glob_match(s1 + 1, s2) || glob_match(s1, s2 + 1));
	else
		return (0);
}

int	glob_match_wrapper(char const **s1, char const **s2)
{
	return (glob_match(*s1, *s2));
}

int	builtin_unsetenv(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		environment_remove_if(argv[i], (t_predf) & glob_match_wrapper);
		if (glob_match(argv[i], "PATH"))
			generate_paths();
		++i;
	}
	return (0);
}
