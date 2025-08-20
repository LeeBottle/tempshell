/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:36:21 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 15:43:36 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_in_charset(char *str, char c)
{
	if (*str == c)
		return (1);
	return (0);
}

static int	txt_size(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (str_in_charset(str, c) == 1)
			str++;
		if (*str == '\0')
			break ;
		while (*str != '\0' && str_in_charset(str, c) == 0)
			str++;
		count++;
	}
	return (count);
}

static void	txt_len(char *str, char c, char **arr, int size)
{
	int	arr_loc;
	int	arr_size;

	arr_loc = 0;
	while (arr_loc < size && *str != '\0')
	{
		arr_size = 0;
		while (str_in_charset(str, c) == 1)
			str++;
		while (*str != '\0' && str_in_charset(str++, c) == 0)
			arr_size++;
		if (arr_size == 0)
			break ;
		arr[arr_loc] = (char *)malloc(sizeof(char) * (arr_size + 1));
		if (arr[arr_loc] == NULL)
		{
			while (arr_loc-- > 0)
				free(arr[arr_loc]);
			free(arr);
			return ;
		}
		arr_loc++;
	}
	arr[arr_loc] = NULL;
}

static void	txt_input(char *str, char c, char **arr, int size)
{
	int	arr_1st_di;
	int	arr_2nd_di;

	arr_1st_di = 0;
	while (arr_1st_di < size)
	{
		arr_2nd_di = 0;
		while (str_in_charset(str, c) == 1)
			str++;
		if (arr[arr_1st_di] == NULL)
			return ;
		while (*str != '\0' && str_in_charset(str, c) == 0)
		{
			arr[arr_1st_di][arr_2nd_di] = *str;
			arr_2nd_di++;
			str++;
		}
		arr[arr_1st_di][arr_2nd_di] = '\0';
		arr_1st_di++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**arr;
	int		i;

	if (s == NULL)
		return (NULL);
	size = txt_size((char *)s, c);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == NULL)
		return (NULL);
	txt_len((char *)s, c, arr, size);
	i = 0;
	while (i < size)
	{
		if (arr[i] == NULL)
		{
			while (i > 0)
				free(arr[i--]);
			free(arr);
			return (NULL);
		}
		i++;
	}
	txt_input((char *)s, c, arr, size);
	return (arr);
}
