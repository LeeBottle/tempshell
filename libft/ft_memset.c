/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:13:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 13:21:07 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	cnt;
	char	*p;

	cnt = 0;
	p = s;
	while (cnt != n)
	{
		p[cnt] = c;
		cnt++;
	}
	return (s);
}
