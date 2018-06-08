/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 02:51:53 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/08 17:32:31 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include <libft.h>
# include "../srcs/globbing/internals.h"

# define MAGIC_OFFSET 0x2

# define DSET " "

char	*deglob(const char *input, char *token, char *blob, char *a, char *b);

#endif
