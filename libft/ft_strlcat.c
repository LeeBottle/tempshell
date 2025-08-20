/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:29:54 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/24 11:04:44 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	cnt;
	size_t	d;
	size_t	s;

	cnt = 0;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (d > size)
		return (size + s);
	while (src[cnt] != '\0' && d + cnt + 1 < size)
	{
		dst[cnt + d] = src[cnt];
		cnt++;
	}
	dst[cnt + d] = '\0';
	return (s + d);
}
