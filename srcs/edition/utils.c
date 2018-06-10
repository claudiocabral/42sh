/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:44:22 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/09 04:29:43 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	Check if the string is only made of spaces or not.
**	@return 1 if there is only spaces, 0 if there is something else.
*/

int					is_only_space(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char				is_operand(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ';')
		return (1);
	return (0);
}

/*
**	@return 1 if the character can be skip, it is used by move_rigt/left.
*/

char				is_skipable(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

/*
**	Check if a quote or double quote is unclose in the current list.
**	@return a define (cf. edition.h) which says if a quote is unclose or -1
**		if everything is close.
*/

void				still_norm(char *quote, char *dquote, char *bquote,
						t_prompt *list)
{
	if (!*dquote && !*bquote && list->c == '\'' && list->prompt_type !=
		HEREDOC)
		*quote = (!*quote) ? 1 : 0;
	if (!*quote && !*bquote && list->c == '"' && list->prompt_type != HEREDOC)
		*dquote = (!*dquote) ? 1 : 0;
	if (!*quote && !*dquote && list->c == '`' && list->prompt_type != HEREDOC)
		*bquote = (!*bquote) ? 1 : 0;
}

char				is_quote_close(t_prompt *list)
{
	char	quote;
	char	dquote;
	char	bquote;

	quote = 0;
	dquote = 0;
	bquote = 0;
	while (list)
	{
		if (list->c == '\\')
			list = (list->next) ? list->next : list->next_list;
		else
			still_norm(&quote, &dquote, &bquote, list);
		list = (list->next) ? list->next : list->next_list;
	}
	if (dquote)
		return (DQUOTE);
	if (quote)
		return (QUOTE);
	if (bquote)
		return (BQUOTE);
	return (-1);
}
