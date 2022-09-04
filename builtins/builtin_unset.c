/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:30:39 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:28:54 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_unset(char **cmd_args, t_env **our_env)
{
	t_env	*var_to_unset;

	while (cmd_args && *cmd_args)
	{
		if (validity_of_var_name(*cmd_args) == 1)
		{
			print_error(*cmd_args, "unset", ": not a valid identifier");
			g_global.exist_status = 1;
		}
		else
		{
			var_to_unset = find_variable(our_env, *cmd_args);
			if (var_to_unset)
				delete_var_env(our_env, var_to_unset);
		}
		cmd_args++;
	}
	return (g_global.exist_status);
}
