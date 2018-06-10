/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localvar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:03:41 by mprevot           #+#    #+#             */
/*   Updated: 2018/06/10 12:03:43 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCALVAR_H
# define LOCALVAR_H

# include <ft_printf.h>
# include <ft_string.h>
# include <libft.h>
# include <array.h>

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
