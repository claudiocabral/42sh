/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:23:06 by jblazy            #+#    #+#             */
/*   Updated: 2018/02/28 14:35:42 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	Write function use by the termcap library.
**	@return int
*/

int			ft_putc(int c)
{
	return (write(1, &c, 1));
}

/*
** Prepare shell
** @return nil
*/

void		set_sh(t_sh *sh)
{
	sh->new_term.c_lflag &= ~(ICANON);
	sh->new_term.c_lflag &= ~(ECHO);
	sh->new_term.c_cc[VMIN] = 1;
	sh->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &sh->new_term);
	tputs(tgetstr("vi", NULL), 1, &ft_putc);
}

/*
** Reset shell
** @return nil
*/

void		reset_sh(t_sh *sh)
{
	sh->new_term.c_lflag |= ICANON;
	sh->new_term.c_lflag |= ECHO;
	tputs(tgetstr("ve", NULL), 1, &ft_putc);
	tcsetattr(0, TCSANOW, &sh->new_term);
}

void		norm_rly(void)
{
	ft_putendl_fd("Could not access to the terminal data base, sorry.", 2);
}

/*
** Prepare shell
** @return nil
*/

void		init_term(t_sh *sh)
{
	char	*term_type;
	int		term_fd;

	term_type = getenv("TERM");
	if (!term_type)
	{
		ft_putstr_fd("Please define a \"TERM\" environment variable", 2);
		ft_putendl_fd(" to specify the type of your terminal.", 2);
		exit(0);
	}
	term_fd = tgetent(NULL, term_type);
	if (term_fd < 0)
		norm_rly();
	else if (term_fd == 0)
	{
		ft_putstr_fd("The terminal type \"", 2);
		ft_putstr_fd(term_type, 2);
		ft_putendl_fd("\" does not exist.", 2);
	}
	if (term_fd <= 0)
		exit(0);
	tcgetattr(0, &sh->new_term);
	set_sh(sh);
}
