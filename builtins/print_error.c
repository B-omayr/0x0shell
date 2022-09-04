/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:26:00 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:26:32 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *arg, char *cmd, char *reason)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(reason, 1);
}
