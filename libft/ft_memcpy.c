/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:10:38 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/24 11:42:35 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	cnt;
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	cnt = 0;
	d = (char *)dest;
	s = (char *)src;
	while (cnt != n)
	{
		d[cnt] = s[cnt];
		cnt++;
	}
	return (dest);
}
