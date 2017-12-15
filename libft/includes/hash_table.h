/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 12:07:27 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 23:24:40 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <stdlib.h>
# include <stdint.h>
# include <libft.h>

# define MURMUR_M 0x5bd1e995
# define MURMUR_R 24
# define H1(x) (x >> 7)
# define H2(x) (x & 0x7f)
# define GET_16_BITS(d) (*((const uint16_t *) (d)))
# define GET_32_BITS(d) (*((const uint32_t *) (d)))

typedef enum	e_hash_ctrl
{
	hash_empty = -128,
	hash_deleted = -2
}				t_hash_ctrl;

typedef uint64_t	(*t_hashf)(void const*);

typedef struct	s_hash_table
{
	uint8_t		*metadata;
	void		*data;
	uint64_t	size;
	uint64_t	capacity;
	uint64_t	content_size;
	t_hashf		hash;
	t_cmpf		cmpf;
}				t_hash_table;

uint64_t		 paul_hsieh_hash(const char * data, int len);
t_hash_table	*hash_table_create(size_t content_size, size_t nbr_elements,
													t_hashf hash, t_cmpf cmpf);
void			*hash_table_insert(t_hash_table *table, void *data);
void			*hash_table_insert(t_hash_table *table, void *data);
size_t			hash_table_find_index(t_hash_table *table, void const *data);
void			*hash_table_find(t_hash_table *table, void const *data);
void			hash_table_free(t_hash_table *table, t_freef freef);
void			hash_table_dump(t_hash_table *table, t_applyf applyf);
void			hash_table_delete(t_hash_table *table, void *data);
uint32_t		murmur_hash_2(const uint8_t *data, int len);
uint64_t		hash_string(const char **str);

#endif
