/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 08:56:53 by youchenn          #+#    #+#             */
/*   Updated: 2022/06/07 02:03:39 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_stack **alst, t_stack *new)
{
	if (!new)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		ft_lstlast(*alst)->next = new;
	}
}
