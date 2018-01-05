/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:55:32 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:40:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_partition(void **array, int low, int high, t_cmpf cmpf)
{
	int			i;
	int			j;
	char const *pivot;
	void		**tmp;

	tmp = 0;
	pivot = array[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (cmpf(array[j], (void *)pivot) < 0)
		{
			++i;
			ft_swap(array + i, array + j, tmp, sizeof(void **));
		}
		++j;
	}
	if (cmpf(array[high], array[i + 1]) < 0)
		ft_swap(array + i + 1, array + high, tmp, sizeof(void **));
	return (i + 1);
}

void	ft_quicksort(void **array, int low, int high, t_cmpf cmpf)
{
	int	p;

	if (low < high)
	{
		p = ft_partition(array, low, high, cmpf);
		ft_quicksort(array, low, p - 1, cmpf);
		ft_quicksort(array, p + 1, high, cmpf);
	}
}
