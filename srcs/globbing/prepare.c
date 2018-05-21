/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:07:17 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 14:03:50 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "internals.h"

/*
** Prepare principals structures
** and helpers
*/

t_bool	prepare_gbuff(t_helper *halp)
{
	halp->file_bak = NULL;
	halp->cur_path = NULL;
	halp->filename = NULL;
	return (TRUE);
}

t_bool	prepare_glob(t_glob *glob)
{
	glob->final_list = NULL;
	glob->gl_pathv = NULL;
	glob->aref = NULL;
	return (TRUE);
}
