/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:46:00 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/29 11:37:52 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_it_numeric_args(char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	print_exit_error(char *arg, char *reason)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd("exit: ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(reason, 1);
	
}

void	built_exit(char **args)
{
	int exit_status;

	exit_status = 255;
	if (args[1])
	{
		if (is_it_numeric_args(args[1]))
		{
			print_exit_error(args[1], " numeric argument required");
			exit(exit_status);
		}
		else if (!is_it_numeric_args(args[1]) && !args[2])
		{
			exit_status = ft_atoi(args[1]) % 256;
			print_exit_error(args[1], "");
			exit(exit_status);
		}
		else if (!is_it_numeric_args(args[1]) && args[2])
			print_exit_error(args[1], " too many arguments");
	}
	else 
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

