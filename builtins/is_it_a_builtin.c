/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_a_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:08:30 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/03 14:04:04 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_it_builtin(char **cmd)
{
   return (!ft_strncmp(cmd[0], "echo", 5) || !ft_strncmp(cmd[0], "cd", 3) ||\
		!ft_strncmp(cmd[0], "pwd", 4) || !ft_strncmp(cmd[0], "export", 7) \
		|| !ft_strncmp(cmd[0], "unset", 6) || !ft_strncmp(cmd[0], "env", 4) ||\
		!ft_strncmp(cmd[0], "exit", 5));
}
