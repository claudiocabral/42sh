/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_adjust.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:19:55 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/15 11:25:40 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_printf.h>

int			nbr_characters(char const *str)
{
	int	nbr;

	nbr = 0;
	while (1)
	{
		while (is_middle_of_unicode(*str))
			++str;
		if (!*str)
			break ;
		++str;
		++nbr;
	}
	return (nbr);
}

void		adjust_terminal(t_terminal *terminal, int nbr_lines)
{
	if (nbr_lines >= terminal->height)
	{
		print_prompt(terminal);
		ft_dprintf(0, "%s", terminal->line->buffer);
	}
	else
	{
		terminal_command(MOVE_UP, nbr_lines);
		terminal_command(MOVE_RIGHT,
				terminal->prompt_size
				+ nbr_characters(terminal->line->buffer));
	}
}

int			choose_possibility(t_array *array, char *str,
		t_terminal *terminal)
{
	char	**it;
	char	*candidate;
	int		size;
	int		max_size;

	ZERO_IF_FAIL((it = (char **)array->begin) == array->end);
	candidate = *it;
	max_size = ft_strlen(candidate);
	while (it != array->end)
	{
		size = 0;
		while (size < max_size && (*it)[size] == candidate[size])
			++size;
		max_size = size;
		++it;
	}
	if ((size_t)size == ft_strlen(str))
		return (print_options(array, terminal));
	max_size = candidate[size];
	candidate[size] = 0;
	if (str)
		terminal_insert_string(terminal,
				candidate + ft_strlen(str));
	candidate[size] = (char)max_size;
	return (1);
}
