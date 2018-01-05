/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:48:26 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:48:59 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <hash_table.h>

void			hash_table_delete(t_hash_table *table, void *data)
{
	size_t	index;

	index = hash_table_find_index(table, data);
	if (index < table->capacity)
		table->metadata[index] = (uint8_t)hash_deleted;
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
