/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:19:09 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:54:54 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERCENT_H
# define PERCENT_H

# include <modifiers.h>

char const	*arg_number(char const *format, t_modifiers *modifiers);
char const	*flag(char const *format, t_modifiers *modifiers);
char const	*precision(char const *format, t_modifiers *modifiers);
char const	*field_width(char const *format, t_modifiers *modifiers);
char const	*star_field_width(char const *format, t_modifiers *modifiers);
char const	*length(char const *format, t_modifiers *modifiers);
char const	*conversion(char const *format, t_modifiers *modifiers);

#endif
