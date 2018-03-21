/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_aggregator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:34:52 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 14:04:28 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <token.h>
#include <execute.h>
#include <unistd.h>

void		swap_fd(t_fd_pair *fd)
{
	int	tmp;

	tmp = fd->to;
	fd->to = fd->from;
	fd->from = tmp;
}

int			check_agreggator(t_token *token)
{
	if (token->begin[0] == '-')
		return (-1);
	if (ft_isdigit(token->begin[0]))
		return (1);
	return (0);
}

t_fd_pair	deal_with_aggregator(t_fd_pair fd)
{
	fd.to = dup(fd.from);
	close(fd.from);
	return (fd);
}
