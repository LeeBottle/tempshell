/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:35:55 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/26 14:39:29 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	cnt;

	cnt = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (NULL);
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (cnt < len)
	{
		ptr[cnt] = s[start + cnt];
		cnt++;
	}
	ptr[cnt] = '\0';
	return (ptr);
}
