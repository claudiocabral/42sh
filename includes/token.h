/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:17:12 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 16:00:02 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <array.h>

typedef enum	e_tag
{
	COMMANDS = 0,
	LIST,
	TOKEN_NIL,
	SIMPLE_COMMAND,
	TOKEN,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	PIPE,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	IF,
	THEN,
	ELSE,
	ELIF,
	FI,
	DO,
	DONE,
	CASE,
	ESAC,
	WHILE,
	UNTIL,
	FOR,
	LBRACE,
	RBRACE,
	LPARENS,
	RPARENS,
	SEMICOLON,
	AND,
	LESS,
	GREATER,
	BANG,
	IN,
	SENTINEL
}				t_tag;

typedef struct	s_token
{
	t_tag		type;
	char const	*begin;
	size_t		size;
}				t_token;

t_token			emit_token(t_tag type, char const *input, int start, int end);
void			fill_token(t_token *token, t_tag type, char const *begin,
																size_t size);
int				add_token(t_array *tokens, t_tag type, char const *begin,
																size_t size);
int				token_newline(char c);
int				token_quote(char c);
int				token_operator(char c);
int				token_delimiter(char c);
char			*token_get_value(t_token *token);

#endif
