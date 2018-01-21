/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:13:51 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/21 15:14:07 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	make_redirection(int from, int mode, t_array *children)
{
	t_tree	**it;

	(void)it;
}

int	redirect(t_tree *tree)
{
	int		from;
	int		mode;

	mode = O_RDRW | O_CREATE;
	if ((t_token *)tree->value->tag == '<')
		from = STDIN_FILENO;
	else if ((t_token *)tree->value->tag == '>')
		from = STDOUT_FILENO;
	else if ((t_token *)tree->value->tag == '>')
	{
		from = STDOUT_FILENO;
		mode |= O_APPEND;
	}
	return (make_redirection(from, mode, tree->children));
}
