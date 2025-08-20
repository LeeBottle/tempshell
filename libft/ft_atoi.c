/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:31:38 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/24 16:25:13 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	len;
	int	num;
	int	mi_pl;

	len = 0;
	num = 0;
	mi_pl = 1;
	while (nptr[len] == 32 || (nptr[len] >= 9 && nptr[len] <= 13))
		len++;
	if (nptr[len] == 45)
	{
		mi_pl = -1;
		len++;
	}
	else if (nptr[len] == 43)
		len++;
	while (nptr[len] >= 48 && nptr[len] <= 57)
	{
		num = num * 10 + (nptr[len] - 48);
		len++;
	}
	return (num * mi_pl);
}
