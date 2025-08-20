/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:36:10 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 17:26:18 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	int		cnt;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	cnt = ft_lstsize(*lst);
	while (cnt-- > 1)
		temp = temp -> next;
	temp -> next = new;
}
