/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collecter_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 08:42:50 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:09:03 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_malloc(size_t size)
{
	void	*head;

	head = malloc(size);
	if (!head)
		print_error("error", "malloc", "malloc fails");
	ft_lstadd_back1(&g_global.free_collect, ft_lstnew1(head));
	return (head);
}

void	collect_libft_readline(void *to_collect)
{
	ft_lstadd_back1(&g_global.free_collect, ft_lstnew1(to_collect));
}

void	free_list(t_free *list)
{
	if (!list)
		return ;
	free_list(list->next);
	free(list->to_free);
	free(list);
}
