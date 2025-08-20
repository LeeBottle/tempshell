/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:50 by byeolee           #+#    #+#             */
/*   Updated: 2025/03/18 17:25:28 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	input_char(char *str, int n, int len, int check)
{
	if (!str)
		return ;
	if (check == 1)
	{
		str[0] = '-';
		len++;
	}
	str[len] = '\0';
	while (len > check)
	{
		str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

static void	allocate(int *n, int *len, int *mi_pl, char **ptr)
{
	int	i;

	*len = 0;
	*mi_pl = 0;
	if (*n < 0)
	{
		*n = -*n;
		*mi_pl = 1;
	}
	i = *n;
	while (i > 0)
	{
		i /= 10;
		(*len)++;
	}
	*ptr = (char *)malloc(sizeof(char) * (*len + *mi_pl + 1));
}

static char	*checker(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

char	*ft_itoa(int n)
{
	int		len;
	int		mi_pl;
	char	*ptr;
	char	*special_case;

	len = 0;
	mi_pl = 0;
	special_case = checker(n);
	if (special_case)
		return (special_case);
	allocate(&n, &len, &mi_pl, &ptr);
	if (!ptr)
		return (NULL);
	input_char(ptr, n, len, mi_pl);
	return (ptr);
}
