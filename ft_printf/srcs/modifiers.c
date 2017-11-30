/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:24:36 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:55:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modifiers.h"

void		init_modifiers(t_modifiers *modifiers, va_list *args)
{
	modifiers->type = NULL_T;
	modifiers->flags = NO_FLAGS;
	modifiers->precision = -1;
	modifiers->field_width = -1;
	modifiers->arg_number = 0;
	modifiers->length = NONE;
	modifiers->separator = 0;
	modifiers->separator_size = 0;
	va_copy(modifiers->args, *args);
}

void		clean_modifiers(t_modifiers *modifiers)
{
	va_end(modifiers->args);
}

void		reset_modifiers(t_modifiers *modifiers)
{
	modifiers->type = NULL_T;
	modifiers->flags = NO_FLAGS;
	modifiers->precision = -1;
	modifiers->field_width = -1;
	modifiers->arg_number = 0;
	modifiers->length = NONE;
	modifiers->separator = 0;
	modifiers->separator_size = 0;
}
