/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:57:56 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/20 14:57:44 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <array.h>
# include <token.h>
# include <slice.h>

int			add_token(t_array *tokens, t_tag type, char const *begin,
															size_t size);
int			push_newline_token(t_array *tokens, char const *input, int start);
int			lex_text(t_array *tokens, t_slice input, char *const *heredoc);
int			lex_digit(t_array *tokens, t_slice input);
int			lex_token(t_array *tokens, t_slice input, int pos);
int			lex_operator(t_array *tokens, t_slice input, char *const *heredoc);
int			lex_quote(t_array *tokens, t_slice input);
int			lex_redirection(t_array *tokens, t_slice input,
										char *const *heredoc);

#endif
