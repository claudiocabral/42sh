/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:13:20 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 23:40:15 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <hash_table.h>

size_t			hash_table_find_index(t_hash_table *table, void const *data)
{
	uint64_t	hash;
	size_t		tmp;
	size_t		i;

	hash = table->hash(data);
	i = H1(hash) & (table->capacity - 1);
	tmp = i;
	while (1)
	{
		if (table->metadata[i] == H2(hash)
				&& table->cmpf(table->data + i * table->content_size, data) == 0)
			return (i);
		i = (i + 1 ) & (table->capacity - 1);
		if (i == tmp)
			return (table->capacity + 1);
	}
}

void			*hash_table_find(t_hash_table *table, void const *data)
{
	size_t	index;

	index = hash_table_find_index(table, data);
	if (index < table->capacity)
		return (table->data + index * table->content_size);
	return (0);
}

void			hash_table_free(t_hash_table *table, t_freef freef)
{
	size_t	i;

	i = 0;
	while (i < table->capacity)
	{
		if (table->metadata[i] != (uint8_t)hash_empty)
			freef(table->data + i * table->content_size);
		++i;
	}
	free(table->metadata);
}
