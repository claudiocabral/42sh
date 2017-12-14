/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:51 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/11 12:21:13 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLMA_H
# define SHELLMA_H

# include <term.h>
# include <array.h>
# include <tree.h>

int				process_input(char const *input);
t_array			*lex(char const *input);
t_tree			*parse(t_array *tokens);
int				execute(t_tree *tree);
void			quit(void);

#endif
