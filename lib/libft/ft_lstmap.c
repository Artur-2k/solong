/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:58:59 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/22 20:10:35 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*current;
	void	*content;

	node = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		current = ft_lstnew(content);
		if (!current)
		{
			del(content);
			ft_lstclear(&node, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&node, current);
		lst = lst->next;
	}
	return (node);
}
