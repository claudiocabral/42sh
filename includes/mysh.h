/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:05:14 by mprevot           #+#    #+#             */
/*   Updated: 2018/06/10 12:05:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSH_H
# define MYSH_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <ft_string.h>
# include <array.h>
# include "libft.h"
# include "ft_printf.h"
# include "builtins.h"
# include "edition.h"
# include "autocompletion.h"
# include "environment.h"
# include "execute.h"
# include "heredoc.h"
# include "lexer.h"
# include "parser.h"
# include "sessions.h"
# include "setup.h"
# include "shellma.h"
# include "signal_handlers.h"
# include "token.h"
# include "localvar.h"

#endif
