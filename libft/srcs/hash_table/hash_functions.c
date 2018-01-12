/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:05:08 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 11:35:56 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <libft.h>
#include <hash_table.h>

uint64_t	paul_hsieh_remainder(uint64_t hash, const char *data, uint8_t rem)
{
	if (rem >= 4)
	{
		hash += GET_32_BITS(data);
		hash ^= hash << 32;
		data += sizeof(uint32_t);
		rem -= 4;
	}
	if (rem == 3)
	{
		hash += GET_16_BITS(data);
		hash ^= ((signed char)data[sizeof(uint16_t)]) << 18;
		hash += hash >> 23;
	}
	else if (rem == 2)
	{
		hash += GET_16_BITS(data);
		hash ^= hash << 23;
		hash += hash >> 37;
	}
	else if (rem == 1)
	{
		hash += (signed char)*data;
		hash ^= (hash << 20) + ((hash << 20) >> 1);
	}
	return (hash);
}

uint64_t	paul_hsieh_hash(const char *data, int len)
{
	uint64_t	hash;
	uint64_t	tmp;
	uint8_t		remainder;

	hash = len;
	remainder = len & 0x7;
	len >>= 3;
	while (len > 0)
	{
		hash += GET_32_BITS(data);
		tmp = (GET_32_BITS(data + 4) << 23) ^ hash;
		hash = (hash << 32) ^ tmp;
		data += sizeof(uint64_t);
		hash += hash >> 23;
		--len;
	}
	hash = paul_hsieh_remainder(hash, data, remainder);
	hash ^= hash << 7;
	hash += hash >> 9;
	hash ^= hash << 8;
	hash += hash >> 37;
	hash ^= hash << 53;
	hash += hash >> 13;
	return (hash);
}

uint64_t	hash_string(const char **str)
{
	return (paul_hsieh_hash(*str, ft_strlen(*str)));
}
