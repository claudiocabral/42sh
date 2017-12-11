/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:45:43 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/11 12:14:01 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <hash_table.h>

t_hash_table	*hash_table_create(size_t size, size_t content_size,
												t_hashf hash, t_cmpf cmpf)
{
	t_hash_table	*hash_table;

	size = ft_next_power_of_two(size);
	ZERO_IF_FAIL(hash_table = (t_hash_table *)malloc(sizeof(t_hash_table)));
	if (!(hash_table->metadata = malloc(size * (content_size + 1))))
	{
		free(hash_table);
		return (0);
	}
	hash_table->data = hash_table->metadata + size;
	ft_memset(hash_table->metadata, hash_empty, size);
	hash_table->hash = hash;
	hash_table->cmpf = cmpf;
	return (hash_table);
}

void static		*hash_table_insert_helper(t_hash_table *table, uint8_t *block,
													size_t capacity, void *data)
{
	uint64_t	hash;
	size_t		i;
	void		*helper;

	hash = table->hash(data);
	i = H1(hash) & (~capacity);
	helper = block + capacity;
	while (1)
	{
		if (block[i] == (uint8_t)hash_empty)
		{
			block[i] = block[i] == (uint8_t)hash_deleted ? block[i] : H2(hash);
			ft_memcpy(helper + i * capacity, data, table->content_size);
			return (helper + i * capacity);
		}
		i = (i + 1) & (~capacity);
	}
}

t_hash_table	*hash_table_increase_size(t_hash_table *table)
{
	size_t	new_size;
	uint8_t	*memory_block;
	size_t	i;

	new_size = ft_next_power_of_two(table->capacity + 1);
	ZERO_IF_FAIL(memory_block = malloc(new_size * (table->content_size + 1)));
	ft_memset(memory_block, hash_empty, new_size);
	i = 0;
	while (i < table->capacity)
	{
		if (table->metadata[i] != (uint8_t)hash_empty)
			hash_table_insert_helper(table, memory_block, new_size,
								table->data + i * table->content_size);
	}
	free(table->metadata);
	table->metadata = memory_block;
	table->capacity = new_size;
	return (table);
}

void			*hash_table_insert(t_hash_table *table, void *data)
{
	if ((float)table->size / (float)table->capacity > 0.7)
		ZERO_IF_FAIL(hash_table_increase_size(table));
	table->size++;
	return (hash_table_insert_helper(table, table->metadata,
											table->capacity, data));
}

void			hash_table_delete(t_hash_table *table, void *data)
{
	size_t	index;

	index = hash_table_find_index(table, data);
	if (index < table->capacity)
		table->metadata[index] = (uint8_t)hash_deleted;
}
