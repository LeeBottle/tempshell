/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:10:05 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 13:50:30 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len1;
	int		len2;

	len1 = 0;
	while (s[len1] != '\0')
		len1++;
	ptr = (char *)malloc(sizeof(char) * (len1 + 1));
	if (ptr == NULL)
		return (NULL);
	len2 = 0;
	while (len2 != len1)
	{
		ptr[len2] = s[len2];
		len2++;
	}
	ptr[len2] = '\0';
	return (ptr);
}
