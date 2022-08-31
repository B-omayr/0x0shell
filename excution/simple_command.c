/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:43:25 by youchenn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/31 16:08:29 by iomayr           ###   ########.fr       */
=======
/*   Updated: 2022/08/31 13:15:28 by youchenn         ###   ########.fr       */
>>>>>>> c059e8d3ee1561cb6eea4f20a5ed27b1b67ba205
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    run_simple_cmd(t_main *main)
{
	char *path;
	char **env;

	path = find_cmd_path(&main->h_env, main->cmd->command[0]);
	env = convert_env_to_matrix(main->h_env);
	execve(path, main->cmd->command, env);
	perror(main->cmd->command[0]);
	exit(1);
}

int simple_command(t_main *v_main)
{
	int pid;

	if (handel_redirections(v_main->cmd) < 0)
        return (1);
	if (v_main->cmd->command)
	{
		if (is_it_builtin(v_main->cmd->command))
			return (excute_builtins(v_main->cmd->command, &v_main->h_env));
		g_global.catch_signal = 1;
		pid = fork();
		if (pid == 0)
			run_simple_cmd(v_main);  
		waitpid(pid, 0, 0);
	}
	return (0);
}
