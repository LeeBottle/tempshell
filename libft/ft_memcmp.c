/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:45:41 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/17 14:05:39 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				cnt;
	unsigned char		*dest;
	const unsigned char	*src;

	cnt = 0;
	dest = (unsigned char *)s1;
	src = (const unsigned char *)s2;
	while (cnt != n)
	{
		if (dest[cnt] != src[cnt])
			return (dest[cnt] - src[cnt]);
		cnt++;
	}
	return (0);
}
