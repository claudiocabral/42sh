/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:36:49 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 14:37:27 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		special_char(char c)
{
	return (c == 'n' || c == 't' || c == 'r'
			|| c == 'f' || c == 'v' || c == 'b');
}

char	get_special_char(char c)
{
	if (c == 'n')
		return ('\n');
	if (c == 't')
		return ('\t');
	if (c == 'r')
		return ('\r');
	if (c == 'f')
		return ('\f');
	if (c == 'v')
		return ('\v');
	if (c == 'b')
		return ('\b');
	return (0);
}
