/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 16:49:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 16:58:27 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <token.h>

int	token_delimiter(char c)
{
	return (token_newline(c) || token_operator(c) || token_white_space(c));
}
