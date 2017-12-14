/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_murmur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:47:25 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/11 13:59:16 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash_table.h>

uint32_t murmur_hash_2(const uint8_t *data, int len)
{
	uint32_t hash;

	hash = len;
	while(len >= 4)
	{
		uint32_t tmp = *(uint32_t*)data;
		tmp *= MURMUR_M;
		tmp ^= tmp >> MURMUR_R;
		tmp *= MURMUR_M;
		hash *= MURMUR_M;
		hash ^= tmp;
		data += 4;
		len -= 4;
	}
	if (len == 3)
		hash ^= data[2] << 16;
	if (len >= 2)
		hash ^= data[1] << 8;
	if (len >= 1)
		hash ^= data[0];
	hash *= MURMUR_M;
	hash ^= hash >> 13;
	hash *= MURMUR_M;
	hash ^= hash >> 15;
	return (hash);
}
