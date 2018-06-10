/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:57:56 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/10 06:21:31 by gfloure          ###   ########.fr       */
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
int			lex_text(t_array *tokens, t_slice input, char const **heredoc);
int			lex_digit(t_array *tokens, t_slice input);
int			lex_token(t_array *tokens, t_slice input, int pos);
int			lex_operator(t_array *tokens, t_slice input, char const **heredoc);
int			lex_quote(t_array *tokens, t_slice input, int posb);
int			lex_var(t_array *tokens, t_slice input, int posb);
int			lex_comment(t_slice input);
int			lex_redirection(t_array *tokens, t_slice input,
										char const **heredoc);
int			get_quote(int quote);
int			skip_char(int skip);
void		change_special_char(char *str);
void		remove_all_quotes(char *token);

#endif
