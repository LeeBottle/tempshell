/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:43:30 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 17:44:55 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_init(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;
	int		cnt;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && check_init(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && check_init(s1[end], set))
		end--;
	ptr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (ptr == NULL)
		return (NULL);
	cnt = 0;
	while (start <= end)
		ptr[cnt++] = s1[start++];
	ptr[cnt] = '\0';
	return (ptr);
}
