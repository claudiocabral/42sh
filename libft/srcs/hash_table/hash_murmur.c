/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_murmur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:47:25 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/11 16:53:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash_table.h>

uint32_t	murmur_hash_2(const uint8_t *data, int len)
{
	uint32_t hash;
	uint32_t tmp;

	hash = len;
	while (len >= 4)
	{
		tmp = *(uint32_t*)data;
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
	return ((hash ^= hash >> 15));
}
