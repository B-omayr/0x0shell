/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 08:41:49 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 08:42:19 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_free	*ft_lstnew1(void *content)
{
	t_free	*node;

	node = (t_free *)malloc(sizeof(t_free));
	if (!node)
		return (NULL);
	node->to_free = content;
	node->next = NULL;
	return (node);
}

t_free	*ft_lstlast1(t_free *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back1(t_free **collecter, t_free *new)
{
	if (!collecter || !new)
		return ;
	new->next = *collecter;
	*collecter = new;
}
