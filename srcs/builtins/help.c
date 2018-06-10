/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 17:21:13 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/10 17:21:40 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void	help_part_two(void)
{
	ft_putstr("Alt + A: Copy to left\n");
	ft_putstr("Alt + V: Paste the selection\n");
	ft_putstr("Alt + S: Remove the selection\n");
	ft_putstr("\n=== Remove command ===\n");
	ft_putstr("Backspace: Remove to the left of your cursor\n");
	ft_putstr("Delete: Remove where your cursor is\n");
	ft_putstr("Control + K: Remove from your cursor to the end of the line\n");
	ft_putstr("Control + U: Remove from the beginning of the line ");
	ft_putstr("to your cursor\n");
	ft_putstr("Control + W: Remove one word left\n");
	ft_putstr("\n=== Control command ===\n");
	ft_putstr("Control + D: Remove where your cursor is or quit the shell ");
	ft_putstr("if the line is empty\n");
	ft_putstr("Control + L: Clear the screen\n");
	ft_putstr("Control + C: Skip the line where you were writing, ");
	ft_putstr("begin a new one\n");
}

int		help(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_putstr("=== Move command ===\n");
	ft_putstr("Arrow right: Move right\n");
	ft_putstr("Arrow left: Move left\n");
	ft_putstr("Alt + Arrow up: Move one column up\n");
	ft_putstr("Alt + Arrow down: Move one column down\n");
	ft_putstr("Alt + Arrow right: Move one word right\n");
	ft_putstr("Alt + Arrow left: Move one word left\n");
	ft_putstr("Home or Control + A: Move to the begin of your line\n");
	ft_putstr("End or Control + E: Move to the end of your line\n");
	ft_putstr("\n=== History command ===\n");
	ft_putstr("Arrow up: Previous command in history\n");
	ft_putstr("Arrow down: Next command in history\n");
	ft_putstr("\n=== Copy/Paste command ===\n");
	ft_putstr("Alt + D: Copy to right\n");
	help_part_two();
	return (1);
}
