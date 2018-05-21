/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/21 15:08:56 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLMA_H
# define SHELLMA_H

# include <term.h>
# include <array.h>
# include <tree.h>

int				process_input(char *input);
t_array			*lex(char const *input);
t_tree			*parse(t_array *tokens);
int				execute(t_tree *tree);

#endif
