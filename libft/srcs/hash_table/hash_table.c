/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:45:43 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:49:02 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <hash_table.h>

t_hash_table	*hash_table_create(size_t content_size, size_t nbr_elements,
		t_hashf hash, t_cmpf cmpf)
{
	t_hash_table	*hash_table;

	nbr_elements = ft_next_power_of_two(nbr_elements);
	ZERO_IF_FAIL(hash_table = (t_hash_table *)malloc(sizeof(t_hash_table)));
	if (!(hash_table->metadata = malloc(nbr_elements * (content_size + 1))))
	{
		free(hash_table);
		return (0);
	}
	hash_table->data = hash_table->metadata + nbr_elements;
	ft_memset(hash_table->metadata, hash_empty, nbr_elements);
	hash_table->hash = hash;
	hash_table->cmpf = cmpf;
	hash_table->capacity = nbr_elements;
	hash_table->content_size = content_size;
	hash_table->size = 0;
	ft_memset(hash_table->data, 0, hash_table->capacity);
	return (hash_table);
}

static void		*hash_table_insert_helper(t_hash_table *table, uint8_t *block,
		size_t capacity, void *data)
{
	uint64_t	hash;
	uint64_t	i;
	void		*helper;

	hash = table->hash(data);
	i = H1(hash) & (capacity - 1);
	helper = block + capacity;
	while (1)
	{
		if (block[i] == (uint8_t)hash_empty)
		{
			block[i] = H2(hash);
			ft_memcpy(helper + i * table->content_size,
					data, table->content_size);
			return (helper + i * table->content_size);
		}
		i = (i + 1) & (capacity - 1);
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
		++i;
	}
	free(table->metadata);
	table->metadata = memory_block;
	table->data = memory_block + new_size;
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

void			hash_table_apply(t_hash_table *table, t_applyf apply)
{
	size_t	i;

	i = 0;
	while (i < table->capacity)
	{
		if (table->metadata[i] != (uint8_t)hash_empty)
		{
			apply(table->data + i * table->content_size, table);
		}
		++i;
	}
}
