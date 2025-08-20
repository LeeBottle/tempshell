/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:48:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 12:16:16 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		whole_cnt;
	int		per_cnt;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	whole_cnt = 0;
	per_cnt = 0;
	while (s1[per_cnt] != '\0')
		ptr[whole_cnt++] = s1[per_cnt++];
	per_cnt = 0;
	while (s2[per_cnt] != '\0')
		ptr[whole_cnt++] = s2[per_cnt++];
	ptr[whole_cnt] = '\0';
	return (ptr);
}
