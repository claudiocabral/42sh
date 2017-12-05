/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:51 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 18:00:30 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLMA_H
# define SHELLMA_H

# include <term.h>

struct s_terminal;

char const		*lex(char const *input);
char const		*parse(char const *input);
void			execute(char const *input);
void			quit(struct s_terminal *terminal);

#endif
