/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:20:55 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/27 17:39:21 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	option_n_enbaled(char **cmd_args)
{
	int i;
	int j;
	int start;

	i = 1;
	start = 1;
	while (cmd_args[i])
	{
		j = 1;
		if (cmd_args[i][0] != '-')
			return (start);
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] != 'n')
				return (start);
			j++;
		}
		start++;
		i++;
	}
	return (start);
}

int	built_echo(char **cmd_args)
{
	int start; 

	start = option_n_enbaled(cmd_args);
	while (cmd_args[start])
	{
		ft_putstr_fd(cmd_args[start], 1);
		if (cmd_args[start + 1])
			ft_putchar_fd(' ', 1);
		start++;
	}
	if (!start)
		ft_putchar_fd('\n', 1);
	return (0);
}
