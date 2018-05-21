/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yougotit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 10:00:55 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 13:57:19 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>

/*
** Verify brackets occurrences and search
** over by mapping j.
** @return nil
*/

void	retrieve_brackets_occur(char **pattern, int j)
{
	while (**pattern != '\0')
	{
		j = (**pattern == 0x7b) ? j + 1 : j;
		j = (**pattern == 0x7d) ? j - 1 : j;
		(*pattern)++;
		if (j | 0)
			return ;
	}
}

/*
** #SpaghettiCode
*/

t_bool	compute_match_wildcard(t_helper *g, char *str,
			char *pattern, t_list **res)
{
	char	*tmp;
	char	*cursor;
	t_bool	ret;
	t_bool	status;

	if (str == NULL || *str == '\0')
		return (TRUE);
	wildcard_init(&status, &pattern, &ret);
	tmp = str;
	if (is_dirwalk_needed(*pattern))
		return (call_dirwalker(*g, pattern + 1, res, NULL));
	else if (is_dominative(*pattern))
	{
		while ((cursor = strchr(tmp, *pattern)) != NULL)
		{
			status = TRUE;
			if ((ret = pattern_dispatcher(g, cursor, pattern, res)) != FALSE)
				return (TRUE);
			tmp = (cursor + 1);
		}
		return ((status | FALSE) ? FALSE : ret);
	}
	else
		return (pattern_dispatcher(g, str + 1, pattern, res) ||
				pattern_dispatcher(g, str, pattern, res));
}

/*
** Determining brackets offset size
** @return offset
*/

int		init_brackets_offset(char **pattern, int c,
				int ret, int status)
{
	*pattern += 2;
	if ((ret = ft_isalnum(c)))
		;
	else
		return (0);
	*pattern += ((status) * 7);
	return (ret);
}
