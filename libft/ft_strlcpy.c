/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:39:06 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/17 13:47:15 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	cnt;
	size_t	s;

	cnt = 0;
	s = 0;
	while (src[s] != '\0')
		s++;
	if (n == 0)
		return (s);
	while (src[cnt] != '\0' && cnt < (n - 1))
	{
		dst[cnt] = src[cnt];
		cnt++;
	}
	dst[cnt] = '\0';
	while (src[cnt] != '\0')
		cnt++;
	return (cnt);
}
