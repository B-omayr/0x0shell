/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:17:42 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/03 09:39:55 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	excute_builtins(char **cmd, t_env **our_env)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (built_echo(cmd));
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (built_cd(cmd[1], our_env));
	if (!ft_strncmp(cmd[0], "pwd", 4))
		return (built_pwd(), 0);
	if (!ft_strncmp(cmd[0], "export", 7))
		return (built_export(cmd, our_env));
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (built_unset(&cmd[1], our_env));
	if (!ft_strncmp(cmd[0], "env", 4))
		return (built_env(our_env), 0);
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (built_exit(cmd), 0);
	return (-2);
}
