#include <mysh.h>

void		sort_possibilites(t_autocompl *pos, t_info *info)
{
	char	*swap;
	int		i;

	i = 0;
	while (i < info->size - 1)
	{
		if (ft_strcmp(pos[i].str, pos[i + 1].str) > 0)
		{
			swap = ft_strdup(pos[i].str);
			ft_strdel(&(pos[i].str));
			pos[i].str = ft_strdup(pos[i + 1].str);
			ft_strdel(&(pos[i + 1].str));
			pos[i + 1].str = swap;
			i = 0;
		}
		else
			i++;
	}
}
