/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:36:01 by byeolee           #+#    #+#             */
/*   Updated: 2025/01/15 17:23:56 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*temp;

	if (lst == NULL)
		return (NULL);
	lst2 = NULL;
	while (lst != NULL)
	{
		temp = (t_list *)malloc(sizeof(t_list));
		if (temp == NULL)
		{
			del(temp -> content);
			free(temp);
			return (NULL);
		}
		temp->content = f(lst->content);
		temp->next = NULL;
		ft_lstadd_back(&lst2, temp);
		lst = lst->next;
	}
	return (lst2);
}
