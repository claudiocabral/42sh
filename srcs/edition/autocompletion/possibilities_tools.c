/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possibilities_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:08:56 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/08 16:08:57 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void			search_builtins(char *str, t_array *array)
{
	auto_complete_push(array, str, ft_strdup("cd"));
	auto_complete_push(array, str, ft_strdup("echo"));
	auto_complete_push(array, str, ft_strdup("env"));
	auto_complete_push(array, str, ft_strdup("exit"));
	auto_complete_push(array, str, ft_strdup("pwd"));
	auto_complete_push(array, str, ft_strdup("setenv"));
	auto_complete_push(array, str, ft_strdup("unsetenv"));
	auto_complete_push(array, str, ft_strdup("export"));
	auto_complete_push(array, str, ft_strdup("unset"));
	auto_complete_push(array, str, ft_strdup("alias"));
	auto_complete_push(array, str, ft_strdup("unalias"));
}

void			sort_possibilites(t_autocompl *pos, t_infocompl *info)
{
	char	*swap;
	int		i;

	i = 0;
	while (i < info->size - 1)
	{
		if (ft_strcmp(pos[i].str, pos[i + 1].str) > 0)
		{
			swap = pos[i].str;
			pos[i].str = pos[i + 1].str;
			pos[i + 1].str = swap;
			i = 0;
		}
		else
			i++;
	}
}

void			free_autocompletion(t_sh *sh)
{
	t_infocompl	*info;
	int			i;

	i = 0;
	info = sh->completion;
	if (!info)
		return ;
	while (i < info->size)
	{
		ft_strdel(&(info->array[i].str));
		i++;
	}
	free(info->array);
	ft_strdel(&info->str);
	free(info);
	sh->completion = NULL;
}
