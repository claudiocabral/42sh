/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localvar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 22:35:42 by gfloure           #+#    #+#             */
/*   Updated: 2018/05/31 23:59:29 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCALVAR_H
# define LOCALVAR_H

#include <ft_printf.h>
#include <ft_string.h>
#include <libft.h>
#include <array.h>

void		set_localvar(char *token, int only_var);
int			token_var_valid(int save);
char		*search_allvar(char *value);
void		replace_var(t_string *str, int *i);
char		*expand_localvar(char *value);
int			ft_prepare_localvar(void);
t_array		*get_localvar_array(void);
char		*ft_getvar_safe(char const *var);
char		*ft_getvar(char const *var);
int			is_valid_var(char *av);
int			export_localvar(char *var);
char		*ft_getenv_b(char const *var);
int			remove_quotes_var(char *s);


#endif
