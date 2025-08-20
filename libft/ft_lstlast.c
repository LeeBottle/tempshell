/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:33:16 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/13 15:37:58 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	cnt;

	cnt = ft_lstsize(lst);
	if (lst == NULL)
		return (NULL);
	while (cnt > 1)
	{
		lst = lst -> next;
		cnt--;
	}
	return (lst);
}
