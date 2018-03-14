/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:57:56 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/14 16:11:22 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <array.h>
# include <token.h>

int			add_token(t_array *tokens, t_tag type, char const *begin,
															size_t size);
int			push_newline_token(t_array *tokens, char const *input, int start);
int			lex_text(t_array *tokens, char const *input, int start);
int			lex_digit(t_array *tokens, char const *input, int start);
int			lex_token(t_array *tokens, char const *input, int start, int pos);
int			lex_operator(t_array *tokens, char const *input, int start);
int			lex_quote(t_array *tokens, char const *input, int start);
int			lex_redirection(t_array *tokens, char const *input, int start);

#endif
