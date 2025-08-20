/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:11:25 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/24 11:47:32 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	cnt;
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	cnt = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		while (cnt < n)
		{
			d[cnt] = s[cnt];
			cnt++;
		}
	}
	else
	{
		cnt = n;
		while (cnt-- > 0)
			d[cnt] = s[cnt];
	}
	return (d);
}
