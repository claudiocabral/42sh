/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:35:01 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/11 12:21:12 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <token.h>
# include <tree.h>
# include <array.h>

int		match(t_token **token, ...);
t_tree	*pipeline(t_tree *tree, t_array *tokens, t_token **current);

#endif
