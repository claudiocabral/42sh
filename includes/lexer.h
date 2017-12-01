/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:57:56 by claudioca         #+#    #+#             */
/*   Updated: 2017/11/30 15:03:54 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum	e_tag
{
	STRING,
	NUMBER
}				t_tag;

typedef struct	s_token
{
	t_tag	tag;
	char	*value;
}				t_token;

#endif
