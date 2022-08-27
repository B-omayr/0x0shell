/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:19:28 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/27 15:05:58 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_env(t_env **our_env)
{
	t_env *tmp;

	tmp = *our_env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
}
