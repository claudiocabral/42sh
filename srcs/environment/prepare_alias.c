/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 04:09:01 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/02 04:45:31 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <builtins.h>
#include <array.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <execute.h>

static t_array *g_alias = 0;

int			good_alias_name(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
		if (tmp[i] == ' ' || tmp[i++] == '\t')
			return (-1);
	return (1);
}

int			remove_quote_value(char *s)
{
	char	quote;

	quote = 0;
	if (s[ft_strchri(s, '=') + 1] == '\"' || s[ft_strchri(s, '=') + 1] == '\'')
		quote = s[ft_strchri(s, '=') + 1];
	if (s[ft_strlen(s) - 1] == quote && s[ft_strlen(s) - 2] != '\\')
	{
		remove_quotes(&s[ft_strlen(s) - 1]);
		remove_quotes(&s[ft_strchri(s, '=') + 1]);
	}
	return (1);
}

int			is_alias(char *line)
{
	char	*tmp;

	if (line)
	{
		if (ft_strncmp(line, "alias", 5) == 0 && line[5] == ' ')
		{
			ZERO_IF_FAIL(tmp = ft_strsub(line, 6, ft_strchri(line, '=') - 6));
			if (good_alias_name(tmp) == 1)
			{
				free(tmp);
				tmp = ft_strdup(line);
				remove_quote_value(tmp);
				array_push_back(get_alias_array(), &tmp);
				return (0);
			}
			tmp ? free(tmp) : 0;
		}
	}
	return (1);
}

int			init_alias(void)
{
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(".42sh_alias", O_CREAT | O_RDWR | O_APPEND, S_IRWXU)) == -1)
		return (-1);
	while (1)
	{
		if ((ret = get_next_line(fd, &line)) == 0)
		{
			is_alias(line);
			ft_strdel(&line);
			close(fd);
			return (1);
		}
		is_alias(line);
		ft_strdel(&line);
	}
	return (-1);
}

t_array		*get_alias_array(void)
{
	return (g_alias);
}

char		*ft_getalias(char const *var)
{
	char	**ptr;
	char	*val;

	val = 0;
	ptr = array_find(g_alias, &var, (t_cmpf) & ft_strncmp_wrapperb);
	if (ptr)
	{
		val = ft_strchr(*ptr, '=');
		val = val ? val + 1 : 0;
	}
	return (val);
}

int			ft_prepare_alias(void)
{
	ZERO_IF_FAIL(g_alias = array_create(sizeof(char *), 32));
	init_alias();
	return (1);
}
