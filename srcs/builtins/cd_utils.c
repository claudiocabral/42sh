/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:16:02 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 18:44:12 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <ft_string.h>

t_string	*set_pwd(char *str)
{
	static t_string	*path = 0;

	if (path == 0)
		path = string_create(32);
	if (!str)
		return (path);
	string_clear(path);
	string_append(path, str);
	return (path);
}

t_string	*clean_path(char *path)
{
	t_string	*str;
	t_string	*pwd;

	ZERO_IF_FAIL(str = string_create(ft_strlen(path)));
	pwd = set_pwd(0);
	string_append(str, path);
	return (str);
}
