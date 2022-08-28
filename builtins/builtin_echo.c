/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:20:55 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/28 18:15:47 by iomayr           ###   ########.fr       */
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
	int size;

	start = option_n_enbaled(cmd_args);
	size = start;
	while (cmd_args[size])
	{
		ft_putstr_fd(cmd_args[size], 1);
		if (cmd_args[size + 1])
			ft_putchar_fd(' ', 1);
		size++;
	}
	if (start == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
