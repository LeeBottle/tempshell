/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:44:56 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/09 13:46:24 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	cnt1;
	size_t	cnt2;

	cnt1 = 0;
	if (little[0] == '\0')
		return (((char *)big));
	while (big[cnt1] != '\0' && cnt1 < len)
	{
		if (big[cnt1] == little[0])
		{
			cnt2 = 0;
			while (little[cnt2] != '\0' && big[cnt1 + cnt2] == little[cnt2] \
					&& (cnt1 + cnt2) < len)
				cnt2++;
			if (little[cnt2] == '\0')
				return ((char *)(big + cnt1));
		}
		cnt1++;
	}
	return (0);
}
