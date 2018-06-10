/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:07:25 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 16:12:23 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <backtick.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>

char	*get_back_tick_content(char *str, size_t pos, char **start, char **stop)
{
	if (!(*start = ft_strchr(str + pos, '`')))
		return (0);
	if (!(*stop = ft_strchr(*start + 1, '`')))
		return (0);
	return (ft_memdup(*start + 1, *stop - *start - 1));
}

int		collect_command_output(char *str, int read_write[2])
{
	int	save_stdout;

	if ((save_stdout = dup(STDOUT_FILENO)) == -1)
		return (0);
	if (pipe(read_write) == -1)
	{
		close(save_stdout);
		return (0);
	}
	dup2(read_write[1], 1);
	close(read_write[1]);
	process_input_after_backtick(str);
	close(1);
	read_write[1] = save_stdout;
	return (1);
}

char	*command_output_to_string(int read_write[2])
{
	char	buffer[1024];
	char	*str;
	char	*tmp;
	int		size;

	str = ft_strdup("");
	while ((size = read(read_write[0], buffer, 1023)))
	{
		if (!str)
			break ;
		buffer[size] = '\0';
		tmp = str;
		str = ft_vjoin(4, str, "\"", buffer, "\"");
		free(tmp);
	}
	dup2(read_write[1], 1);
	close(read_write[0]);
	close(read_write[1]);
	if (size == -1)
	{
		free(str);
		str = 0;
	}
	return (str);
}

char	*replace_backtick(char *str, char *new_str, char *begin, char *end)
{
	char	*result;

	result = ft_strreplace(str, new_str, begin - str, end - str);
	free(str);
	result = backticks_replace(result, (begin - str) + ft_strlen(new_str));
	free(new_str);
	return (result);
}
