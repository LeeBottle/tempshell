/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:33:05 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/10 14:33:14 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		cnt;
	char	*ptr;

	len = 0;
	while (s[len] != '\0')
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	cnt = 0;
	while (cnt != len)
	{
		ptr[cnt] = f(cnt, s[cnt]);
		cnt++;
	}
	ptr[cnt] = '\0';
	return (ptr);
}
