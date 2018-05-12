#include <libft.h>
#include <environment.h>

void	set_shlvl(void)
{
	char	*level;
	int		value;
	char	*str;

	level = ft_getenv_safe("SHLVL");
	value = ft_atoi(level);
	if (!(str = ft_itoa(value + 1)))
		return ;
	ft_setenv("SHLVL", str, 1);
	free(str);
}
