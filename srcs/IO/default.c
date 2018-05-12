#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <shellma.h>
#include <signal_handlers.h>
#include <signal.h>
#include <term.h>
#include <environment.h>
#include <io.h>

t_terminal	*default_terminal(t_terminal *terminal)
{
	static t_terminal	*term = 0;

	if (terminal)
		term = terminal;
	return term;
}
