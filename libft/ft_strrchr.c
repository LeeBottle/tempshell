/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:05:25 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 13:37:02 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	while (cnt >= 0)
	{
		if (s[cnt] == (char)c)
			return ((char *)&s[cnt]);
		cnt--;
	}
	return (NULL);
}
